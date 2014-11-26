#pragma once
#include "qthread.h"
class AlgorithmThread :
	public QThread
{

public:
	AlgorithmThread();
	~AlgorithmThread();

	void run();
};

