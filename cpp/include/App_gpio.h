
#define GPIO_LED_BLUE 26
#define GPIO_LED_GREEN 27
#define GPIO_LED_RED 164

#define RED			1
#define GREEN		2
#define BLUE		4

#define YELLOW		3
#define MAGENTA	5
#define CYAN		6
#define WHITE		7


#define MAX_BUF 64
#define SYSFS_GPIO_DIR "/sys/class/gpio"



int gpiopps_export(unsigned int gpio);
int gpiopps_set_dir(unsigned int gpio, const char* dir);
int gpiopps_get_value(unsigned int gpio, unsigned int *value);
void init_front_leds();
