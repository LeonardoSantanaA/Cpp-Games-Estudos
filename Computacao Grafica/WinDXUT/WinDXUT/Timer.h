#ifndef DXUT_TIMER_H
#define DXUT_TIMER_H

#include <windows.h>

class Timer {
private:
	LARGE_INTEGER start, end; //valores de inicio e fim do contador
	LARGE_INTEGER freq; //frequencia do contador
	bool stopped;	//estado da contagem

public:
	Timer();
	void Start();	//inicia/retoma contagem do tempo
	void Stop();	//para contagem do tempo
	float Reset();	//reinicia contagem e retorna tempo transcorrido
	float Elapsed();	//retorna tempo transcorrido em segundo
	bool Elapsed(float secs);	//verifica se transcorreu "secs" em segundos
};

inline bool Timer::Elapsed(float secs) {
	return (Elapsed() >= secs ? true : false);
}

#endif