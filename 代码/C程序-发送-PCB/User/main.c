//==========头文件============
#include "stm32f10x.h"
#include "gpio.h"
#include "spi.h"
#include "usart.h"
#include "delay.h"
#include "MyDelay.h"
#include "24L01.h"
#include "stdio.h"
#include "MPU6050.h"

#include "string.h"
#include "math.h"

#include "nnom.h"
#include "weights.h"

//========常见字符扫描码========
#define KEY_A 0x04
#define KEY_B 0x05
#define KEY_C 0x06
#define KEY_D 0x07
#define KEY_E 0x08
#define KEY_F 0x09
#define KEY_G 0x0A
#define KEY_H 0x0B
#define KEY_I 0x0C
#define KEY_J 0x0D
#define KEY_K 0x0E
#define KEY_L 0x0F
#define KEY_M 0x10
#define KEY_N 0x11
#define KEY_O 0x12
#define KEY_P 0x13
#define KEY_Q 0x14
#define KEY_R 0x15
#define KEY_S 0x16
#define KEY_T 0x17
#define KEY_U 0x18
#define KEY_V 0x19
#define KEY_W 0x1A
#define KEY_X 0x1B
#define KEY_Y 0x1C
#define KEY_Z 0x1D
#define KEY_SPACE 0x2C
#define KEY_ENTER 0x28
#define KEY_1 0x1E
#define KEY_2 0x1F
#define KEY_3 0x20
#define KEY_4 0x21
#define KEY_5 0x22
#define KEY_6 0x23
#define KEY_7 0x24
#define KEY_8 0x25
#define KEY_9 0x26
#define KEY_0 0x27

//========NRF24L01+模块连线========
/*
CSN		PB12
CE		PA8
MOSI	PB15
SCK		PB13
IRQ		没有用到
MISO	PB14
*/

//------------------------------------------------------------------------------
uint8_t key_new[6]; // 扫描5个按键的数组  每个数存储一个按键的值   按下是1   不按是0
uint8_t key_old[6]; // 用于存储上一次的按键值

uint8_t isRecording = 0; // 是否在录制

uint8_t result = 100; // 动作识别的结果

#ifdef NNOM_USING_STATIC_MEMORY	//使用静态内存
static int8_t nnom_buffer[8 * 1024];
#endif


nnom_model_t *model;

#define QUANTIFICATION_SCALE (pow(2, INPUT_1_OUTPUT_DEC))
#define CALIBRATION_SAMPLES 5 // 使用前5行进行校准
#define ALPHA 0.3f // 低通滤波系数 (0-1之间，越小滤波越强)
#define maxlength 100

int16_t AX, AY, AZ, GX, GY, GZ; // 定义用于存放各个数据的变量
uint8_t motion_index = 0;
float mpu6050_acc[maxlength][3] = {0};
float calibration_mean[3] = {0}; // 存储前三列的平均值
float filtered_acc[maxlength][3] = {0};     // 存储滤波后的数据

void low_pass_filter(float *input, float *output, float alpha, int is_first_run) 
{
    if (is_first_run) {
        *output = *input;  // 第一次运行时直接赋值
    } else {
        *output = alpha * (*input) + (1 - alpha) * (*output);
    }
}

void apply_low_pass_filter()// 批量低通滤波处理
{
    for (int i = 0; i < maxlength; i++) {
        for (int j = 0; j < 3; j++) {
            low_pass_filter(&mpu6050_acc[i][j], &filtered_acc[i][j], ALPHA, (i == 0));
        }
    }
}

void nnom_feed_input() // 模型数据输入
{
    uint8_t i = 0;
    double scale = QUANTIFICATION_SCALE;
			
    // 应用低通滤波（每列独立滤波）
    for (int col = 0; col < 3; col++) {
        for (i = 0; i < maxlength; i++) {
            if (i == 0) {
                filtered_acc[i][col] = mpu6050_acc[i][col]; // 第一个数据直接使用
            } else {
                filtered_acc[i][col] = ALPHA * mpu6050_acc[i][col] + (1 - ALPHA) * filtered_acc[i-1][col];
            }
        }
    }

    // 计算校准平均值（使用前CALIBRATION_SAMPLES行滤波后的数据）
   for (int col = 0; col < 3; col++)
        {
            calibration_mean[col] = 0;
            for (i = 0; i < CALIBRATION_SAMPLES; i++)
            {
                calibration_mean[col] += filtered_acc[i][col];
            }
            calibration_mean[col] /= CALIBRATION_SAMPLES;
        }

    // 处理数据并量化
    for (i = 0; i < maxlength; i++)
    {
        float processed_value;

        float acc0 = filtered_acc[i][0];
        float acc1 = filtered_acc[i][1];
        float acc2 = filtered_acc[i][2];
 
        // 第1列：减去平均值后除以1000
        processed_value = (acc0 - calibration_mean[0]) / 1000.0f;
        nnom_input_data[i * 3] = (int8_t)round(processed_value * scale);

        // 第2列：减去平均值后除以1000
        processed_value = (acc1 - calibration_mean[1]) / 1000.0f;
        nnom_input_data[i * 3 + 1] = (int8_t)round(processed_value * scale);

        // 第3列：减去平均值后除以2000
        processed_value = (acc2 - calibration_mean[2]) / 2000.0f;
        nnom_input_data[i * 3 + 2] = (int8_t)round(processed_value * scale);
    }
}

void nnom_get_output() // 模型结果输出
{
    model_run(model);

    float max_output = -1;
    uint8_t max_i = 100;

    uint8_t i = 0;
    for (i = 0; i < 10; i++)
    {
        float output = (float)nnom_output_data[i] / 127 * 100;
				printf("output[%d] = %f %%\n",i,output);
        if (output > max_output)
        {
            max_output = output;
            max_i = i;
        }
    }
    result = max_i;
}

void send_result(uint8_t result) // 根据识别到的结果发送对应按键
{
    if (result == 1)
    {
        Send_2401(KEY_1);           // 无线发送数据   代表1键按下了
        printf("1_Lumos\n");
        delay_ms(100);

        Send_2401(0x00); // 无线发送数据   0x00是按键清零
        delay_ms(100);
        Send_2401(0x00); // 无线发送数据   0x00是按键清零   再次发送，防止收不到数据
    }
    else if (result == 2)
    {
        Send_2401(KEY_2);           // 无线发送数据   代表2键按下了
        printf("2_Stupefy\n");
        delay_ms(100);

        Send_2401(0x00); // 无线发送数据   0x00是按键清零
        delay_ms(100);
        Send_2401(0x00); // 无线发送数据   0x00是按键清零   再次发送，防止收不到数据
    }
    else if (result == 3)
    {
        Send_2401(KEY_3);           // 无线发送数据   代表3键按下了
        printf("3_Alohomora\n");
        delay_ms(100);

        Send_2401(0x00); // 无线发送数据   0x00是按键清零
        delay_ms(100);
        Send_2401(0x00); // 无线发送数据   0x00是按键清零   再次发送，防止收不到数据
    }
    else if (result == 4)
    {
        Send_2401(KEY_4);           // 无线发送数据   代表4键按下了
        printf("4_Oppugno\n");
        delay_ms(100);

        Send_2401(0x00); // 无线发送数据   0x00是按键清零
        delay_ms(100);
        Send_2401(0x00); // 无线发送数据   0x00是按键清零   再次发送，防止收不到数据
    }
    else if (result == 5)
    {
        Send_2401(KEY_5);           // 无线发送数据   代表5键按下了
        printf("5_Avada Kedavra\n");
        delay_ms(100);

        Send_2401(0x00); // 无线发送数据   0x00是按键清零
        delay_ms(100);
        Send_2401(0x00); // 无线发送数据   0x00是按键清零   再次发送，防止收不到数据
    }
    else if (result == 6)
    {
        Send_2401(KEY_6);           // 无线发送数据   代表6键按下了
        printf("6_Metelojinx Recanto\n");
        delay_ms(100);

        Send_2401(0x00); // 无线发送数据   0x00是按键清零
        delay_ms(100);
        Send_2401(0x00); // 无线发送数据   0x00是按键清零   再次发送，防止收不到数据
    }
    else if (result == 7)
    {
        Send_2401(KEY_7);           // 无线发送数据   代表7键按下了
        printf("7_Reparo\n");
        delay_ms(100);

        Send_2401(0x00); // 无线发送数据   0x00是按键清零
        delay_ms(100);
        Send_2401(0x00); // 无线发送数据   0x00是按键清零   再次发送，防止收不到数据
    }
    else if (result == 8)
    {
        Send_2401(KEY_8);           // 无线发送数据   代表8键按下了
        printf("8_Expelliarmus\n");
        delay_ms(100);

        Send_2401(0x00); // 无线发送数据   0x00是按键清零
        delay_ms(100);
        Send_2401(0x00); // 无线发送数据   0x00是按键清零   再次发送，防止收不到数据
    }
    else if (result == 9)
    {
        Send_2401(KEY_9);           // 无线发送数据   代表9键按下了
        printf("9_Expecto Patronum\n");
        delay_ms(100);

        Send_2401(0x00); // 无线发送数据   0x00是按键清零
        delay_ms(100);
        Send_2401(0x00); // 无线发送数据   0x00是按键清零   再次发送，防止收不到数据
    }
    else if (result == 0)
    {
        Send_2401(KEY_0);           // 无线发送数据   代表0键按下了
        printf("10_Incendio\n");
        delay_ms(100);

        Send_2401(0x00); // 无线发送数据   0x00是按键清零
        delay_ms(100);
        Send_2401(0x00); // 无线发送数据   0x00是按键清零   再次发送，防止收不到数据
    }
}

// 扫描按键，并处理，如果有按键按下了，新的按键值是0，上一次的按键值是1，就说明有按键按下的动作
void read_key(void)
{
    key_new[0] = READ_B0;  // 读端口PB0电平，不按是1   按下是0 ==W
    key_new[1] = READ_A7;  // 读端口PB10电平，不按是1   按下是0 ==A
    key_new[2] = READ_B10; // 读端口PA7电平，不按是1   按下是0 ==S
    key_new[3] = READ_B11; // 读端口PB11电平，不按是1   按下是0 ==D
    key_new[4] = READ_B1;  // 读端口PB10电平，不按是1   按下是0 ==Space
    key_new[5] = READ_A6;  // 读端口PA6电平，不按是1   按下是0 ==Recoed

    // W
    if ((key_new[0] == 0) && (key_old[0] == 1)) // key1 按下   发W按下
    {
        Send_2401(KEY_W);           // 无线发送数据   0x1A是按键值   代表W键按下了
        delay_ms(100);
    }
    if ((key_new[0] == 1) && (key_old[0] == 0)) // key1 抬起   发8个字节0
    {
        Send_2401(0x00); // 无线发送数据   0x00是按键清零
        delay_ms(100);
        Send_2401(0x00); // 无线发送数据   0x00是按键清零   再次发送，防止收不到数据
    }

    // A
    if ((key_new[1] == 0) && (key_old[1] == 1)) // key2 按下   发A按下
    {
        Send_2401(KEY_A);           // 无线发送数据   0x04是按键值  代表A键按下了
        delay_ms(100);
    }
    if ((key_new[1] == 1) && (key_old[1] == 0)) // key2 抬起   发8个字节0
    {
        Send_2401(0x00); // 无线发送数据   0x00是按键清零
        delay_ms(100);
        Send_2401(0x00); // 无线发送数据   0x00是按键清零   再次发送，防止收不到数据
    }

    // S
    if ((key_new[2] == 0) && (key_old[2] == 1)) // key3 按下   发S按下
    {
        Send_2401(KEY_S);           // 无线发送数据   0x16是按键值  代表S键按下了
        delay_ms(100);
    }
    if ((key_new[2] == 1) && (key_old[2] == 0)) // key3 抬起   发8个字节0
    {
        Send_2401(0x00); // 无线发送数据   0x00是按键清零
        delay_ms(100);
        Send_2401(0x00); // 无线发送数据   0x00是按键清零   再次发送，防止收不到数据
    }

    // D
    if ((key_new[3] == 0) && (key_old[3] == 1)) // key4 按下   发D按下
    {
        Send_2401(KEY_D); // 无线发送数据   0x07是按键值  代表D键按下了
        delay_ms(100);
    }
    if ((key_new[3] == 1) && (key_old[3] == 0)) // key4 抬起   发8个字节0
    {
        Send_2401(0x00); // 无线发送数据   0x00是按键清零
        delay_ms(100);
        Send_2401(0x00); // 无线发送数据   0x00是按键清零   再次发送，防止收不到数据
    }

    // Space
    if ((key_new[4] == 0) && (key_old[4] == 1)) // key5 按下   发Space按下
    {
        Send_2401(KEY_SPACE); // 无线发送数据   0x07是按键值  代表D键按下了
        delay_ms(100);
    }
    if ((key_new[4] == 1) && (key_old[4] == 0)) // key5 抬起   发8个字节0
    {
        Send_2401(0x00); // 无线发送数据   0x00是按键清零
        delay_ms(100);
        Send_2401(0x00); // 无线发送数据   0x00是按键清零   再次发送，防止收不到数据
    }

    // 控制录制
    if ((key_new[5] == 0) && (key_old[5] == 1)) // key5按下  认为按完一次按钮
    {
        if(!isRecording)
			{
				isRecording = 1;
				printf("Start\n");
			}
			else if(isRecording)
			{
				isRecording = 0;
				motion_index = 0;
				printf("End\n");
				
				nnom_feed_input();
        nnom_get_output();
        send_result(result);
				
				result = 100;
        memset(mpu6050_acc, 0, sizeof(mpu6050_acc));
				memset(calibration_mean,0,sizeof(calibration_mean));
			}
    }

    key_old[0] = key_new[0]; // 将新的按键值保存一下，用于下一次的比较
    key_old[1] = key_new[1]; //
    key_old[2] = key_new[2]; //
    key_old[3] = key_new[3]; //
    key_old[4] = key_new[4]; //
    key_old[5] = key_new[5]; //
}

int main(void)
{
    SystemInit(); // 系统时钟初始化
    GPIO_init(GPIO_A, GPIO_Pin_8, GPIO_Mode_Out_PP); // CE  24L01 端口初始化

    // 必须开usart，必须重定向printf，不然nnom_model_create()会卡死
    USART1_config(115200); // 串口1初始化  用于串口打印调试
    printf("uart1_ok\n");  // 打印一个字符串

    SPI2_Init_fun(); // 硬件SPI2  初始化  用于和24L01 通讯

    send_data_init(); // 2401发送的8个字节初始化

    TX_2401_init_send(); // 24L01  初始化为发送模式

    //========按键端口初始化=======================================
    GPIO_init(GPIO_B, GPIO_Pin_11, GPIO_Mode_IPU); // PB11
    GPIO_init(GPIO_B, GPIO_Pin_10, GPIO_Mode_IPU); // PB10
    GPIO_init(GPIO_B, GPIO_Pin_1, GPIO_Mode_IPU);  // PB1
    GPIO_init(GPIO_B, GPIO_Pin_0, GPIO_Mode_IPU);  // PB0
    GPIO_init(GPIO_A, GPIO_Pin_7, GPIO_Mode_IPU);  // PA7
    GPIO_init(GPIO_A, GPIO_Pin_6, GPIO_Mode_IPU);  // PA6 录制控制
    //------------------------------------------------------------
		
    //=========MPU6050================
    MPU6050_Init(); // MPU6050初始化
    //--------------------------------

#ifdef NNOM_USING_STATIC_MEMORY
    nnom_set_static_buf(nnom_buffer, sizeof(nnom_buffer));
#endif
    model = nnom_model_create();

    while (1)
    {
        MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
				read_key(); // 扫描按键，并执行无线发送数据和屏幕的操作
			
				if(isRecording)//如果在录制
				{
					printf("%d,%d,%d,%d,%d,%d\n", AX, AY, AZ, GX, GY, GZ);
          mpu6050_acc[motion_index][0] = AX;
          mpu6050_acc[motion_index][1] = AY;
          mpu6050_acc[motion_index][2] = AZ;
          motion_index++;
					
					if(motion_index >= maxlength)
					{
						motion_index = 0;
						isRecording = 0;
						printf("End\n");
						
						nnom_feed_input();
            nnom_get_output();
            send_result(result);
						
						result = 100;
            memset(mpu6050_acc, 0, sizeof(mpu6050_acc));
						memset(filtered_acc, 0, sizeof(filtered_acc));
						memset(calibration_mean,0,sizeof(calibration_mean));
					}
				}
   }
}

/// 重定向c库函数printf到串口，重定向后可使用printf函数  需要设置一下  在target 中 USE Micro Lib 打钩 才能用  在上面添加   #include "stdio.h"
int fputc(int ch, FILE *f) // 有个问题  函数没有声明  也可以用
{
    /* 发送一个字节数据到串口 */
    USART_SendData(USART1, (uint8_t)ch);

    /* 等待发送完毕 */
    while (!(USART1->SR & USART_FLAG_TXE))
        ;

    return (ch);
}
