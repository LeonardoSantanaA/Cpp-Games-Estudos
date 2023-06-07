#include <iostream>
#include <ctime>
#include <string>

class Time{
  public:
    void Init(); 
    void SetHour(int h);
    void SetMinute(int m);
    void SetSeconds(int s);
    int GetHour();
    int GetMinute();
    int GetSeconds(); 
    void Display12Format(int h, int m, int s);
    void Display24Format(int h, int m, int s);   

  private:
    int hour;
    int minute;
    int seconds;
    void FormatHour(std::string& str, int& h);
};

void Time::Init(){
  time_t timer;
  struct tm* localTimer;

  time(&timer);
  localTimer = localtime(&timer);

  SetHour(localTimer->tm_hour);
  SetMinute(localTimer->tm_min);
  SetSeconds(localTimer->tm_sec);
}
void Time::SetHour(int h){
  hour = h;
}
void Time::SetMinute(int m){
  minute = m;
}
void Time::SetSeconds(int s){
  seconds = s;
}

int Time::GetHour(){
  return hour;
}
int Time::GetMinute(){
  return minute;
}
int Time::GetSeconds(){
  return seconds;
}
   
void Time::Display12Format(int h, int m, int s){
  std::string strTime = " ";
  
  FormatHour(strTime, h);  

  std::cout << "12 hour format:\n";
  std::cout << h << ":" << m << ":" << s << " "<< strTime << " - " << h << " hours, " << m << " minutes and " << s << " seconds" << std::endl;
}

void Time::Display24Format(int h, int m, int s){
  std::string strTime = " ";
  std::cout << "24 hour format:\n";
  std::cout << h << ":" << m << ":" << s << " - ";

  FormatHour(strTime, h);

  std::cout << "this is " << h << ":" << m << ":" << s << " " << strTime << " in 12 hour time" << std::endl;
}

void Time::FormatHour(std::string& str, int& h){
  if(h == 0){
    h = 12;
    str = "AM";
  }else if(h >= 1 && h < 12){
    str = "AM";
  }else if(h >= 13 && h < 23){
    h-=12;
    str = "PM";

  }
}

int main( int argc , char **argv ){
  Time time;
  time.Init();
  time.Display12Format(time.GetHour(), time.GetMinute(), time.GetSeconds());
  time.Display24Format(time.GetHour(), time.GetMinute(), time.GetSeconds());


  return 0;
}

