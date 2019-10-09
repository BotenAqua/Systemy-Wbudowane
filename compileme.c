#include <webots/robot.h>
#include <webots/led.h>
#include <webots/distance_sensor.h>

#define TIME_STEP     64
#define ON            1
#define OFF           0
#define NB_LEDS       10
#define NB_DIST_SENS  8

int main(int argc, char *argv[]) {
  
  WbDeviceTag led[NB_LEDS];
  WbDeviceTag ps[NB_DIST_SENS];
  int licznik[NB_LEDS];
  
  wb_robot_init();
  int it;

  /* przygotowanie diod */
  char text[5] = "led0";
  for(it=0; it<NB_LEDS; it++) {
    led[it] = wb_robot_get_device(text);
    text[3]++;
    wb_led_set(led[it],OFF);
  }
  /* przygotowanie czujnikow odleglosci */
  char textPS[] = "ps0";
  for (it=0; it<NB_DIST_SENS; it++) {
    ps[it] = wb_robot_get_device(textPS);
    textPS[2]++;
    wb_distance_sensor_enable(ps[it],2*TIME_STEP);
  }
    
  int aktualnyLED = 0;
  int sumPS;
  wb_led_set(led[aktualnyLED %= NB_LEDS], ON);
  /* glowna petla programu */
  while (wb_robot_step(TIME_STEP)!=-1) {	
	sumPS = 0;
   
    for (it=0;it<NB_LEDS;it++) {
	  if (wb_distance_sensor_get_value(ps[it]) > 500) {
		  wb_led_set(led[it], ON);
		  licznik[it] = 0;
	  }
	  licznik[it] += 1;
		if (licznik[it] > 100) {
			licznik[it] = 0;
			wb_led_set(led[it], OFF);
		}
	}
  }
  
  wb_robot_cleanup();
  
  return 0;
}
