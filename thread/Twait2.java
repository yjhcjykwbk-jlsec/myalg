// Test obj's "wait-queue" and "lock-queue" 
// notifyAll will put all threads in wait-queue out
// All threads out will then go through lock-queue again

public class Twait2 {

  public static void main(String[] args) {
    TestThread [] ths = new TestThread[30000];
    for(int i = 0; i<30000; i++){
      ths[i] = new TestThread(""+i);
      ths[i].start();
    }

    System.out.println("主线程休眠5秒");
    try {
      Thread.sleep(1000 * 5);
    } catch (InterruptedException e) {
      System.out.println("主线程 Interrupted");
    }

    System.out.println("唤醒所有 By NotifyAll");
    TestThread.resumeByNotifyAll();
    for(int i = 0; i<30000; i++){
      try{
        ths[i].join();
      }catch(Exception e){
      }
    }
    System.out.println("The result: "+TestThread.t);
  }
}

class TestThread extends Thread {

  private static Object obj = new Object();
  public static int t = 0;
  public TestThread(String t){
    super(t);
  }
  @Override
    public void run() {

      synchronized (obj) { //obj lock-queue
        System.out.println(getName() + "come in");
        try {
          obj.wait();      // obj wait-queue
        } catch (InterruptedException e) {
          System.out.println(getName() + " Test Thread Interrupted");
        }
        System.out.println(getName() + "after wait");
        t++;
        System.out.println(getName() + "come out");
      }
    }

  public void resumeByNotify() {
    synchronized (obj) {
      System.out.println(getName() + " go to notify()");
      obj.notify();
    }
  }

  public static void resumeByNotifyAll() {
    synchronized (obj) {
      obj.notifyAll();
    }
  }
}

