#ifndef TIMEOUTLISTENER_H
#define TIMEOUTLISTENER_H

class TimeOutListener{
public:
   virtual void getTestResult(int testId, int boardId) = 0;

};


#endif // TIMEOUTLISTENER_H
