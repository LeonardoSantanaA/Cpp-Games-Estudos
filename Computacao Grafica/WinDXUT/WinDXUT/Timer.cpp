#include "Timer.h"
#include "Types.h"

Timer::Timer() {
	//pega frequencia do contador de alta resolucao
	QueryPerformanceFrequency(&freq);

	//zera os valores de inicio e fim da contagem
	ZeroMemory(&start, sizeof(start));
	ZeroMemory(&end, sizeof(end));

	//timer em funcionamento
	stopped = false;
}

void Timer::Start() {
	if (stopped) {
		//tempo transcorrido antes da parada
		llong elapsed = end.QuadPart - start.QuadPart;

		//leva em conta tempo ja transcorrido antes da parate
		QueryPerformanceCounter(&start);
		start.QuadPart -= elapsed;

		//retoma contagem normal
		stopped = false;
	}
	else {
		//inicia contagem do tempo
		QueryPerformanceCounter(&start);
	}
}

void Timer::Stop() {
	if (!stopped) {
		//marca ponto de parada do tempo
		QueryPerformanceCounter(&end);
		stopped = true;
	}
}

float Timer::Reset() {
	llong elapsed;

	if (stopped) {
		//pega o tempo transcorrido antes da parada
		elapsed = end.QuadPart - start.QuadPart;

		//reinicia contagem do tempo
		QueryPerformanceCounter(&start);

		//contagem reativada
		stopped = false;
	}
	else {
		//finaliza contagem do tempo
		QueryPerformanceCounter(&end);

		//calcula tempo transcorrido (em ciclos)
		elapsed = end.QuadPart - start.QuadPart;

		//reinicia contador
		start = end;
	}

	//converte tempo para segundos
	return float(elapsed / double(freq.QuadPart));
}

float Timer::Elapsed() {
	llong elapsed;

	if (stopped) {
		//pega tempo transcorrido ate a parada
		elapsed = end.QuadPart - start.QuadPart;
	}
	else {
		//finaliza contagem do tempo
		QueryPerformanceCounter(&end);

		//calcula tempo transcorrido (em ciclos)
		elapsed = end.QuadPart - start.QuadPart;
	}

	//converte tempo para segundos
	return float(elapsed / double(freq.QuadPart));
}