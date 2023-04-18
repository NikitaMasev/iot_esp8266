#include "Tasker.h"

void Tasker::runMainTasks(CallbackTaskerLoop taskNetwork, CallbackTaskerLoop taskDataPusher) {
  os.attach(0, taskNetwork, 100);  //50 OK 100??? 250 OK
  os.attach(1, taskDataPusher, 150);
}

void Tasker::runUpsTasks(CallbackTaskerLoop taskCooler, CallbackTaskerLoop taskTemp, CallbackTaskerLoop taskVoltCurSensor) {
  os.attach(2, taskCooler, 5000);
  os.attach(3, taskTemp, 400);
  os.attach(4, taskVoltCurSensor, 200);
}

void Tasker::runRgbaAddressTask(CallbackTaskerLoop taskRgba) {
  os.attach(2, taskRgba, 10);  //10 OK 20??
}

void Tasker::runTempTask(CallbackTaskerLoop taskTemp) {
  os.attach(2, taskTemp, 400);
}

void Tasker::runGestureDetector(CallbackTaskerLoop taskGestureDetector) {
  os.attach(3, taskGestureDetector, 70);  
}

void Tasker::tick() {
  os.tick();
}