
 
public class Twait {
 
 public static void main(String[] args) {
   TestThread testThread1 = new TestThread("a");
         TestThread testThread2 = new TestThread("b");
         TestThread testThread3 = new TestThread("c");
 
         testThread1.start();
         testThread2.start();
         testThread3.start();
 
         System.out.println("主线程休眠5秒");
         try {
             Thread.sleep(1000 * 5);
         } catch (InterruptedException e) {
             System.out.println("主线程 Interrupted");
         }
 
         System.out.println("唤醒 线程Thread-0");
 
         testThread2.resumeByNotify();
 
         try {
          System.out.println("主线程再次休眠");
             Thread.sleep(1000 * 5);
         } catch (InterruptedException e) {
             System.out.println("Main Thread Interrupted");
         }
 
         System.out.println("唤醒所有 By NotifyAll");
 
         testThread1.resumeByNotifyAll();
 
 }
 
}
 
class TestThread extends Thread {
 
 private static Object obj = new Object();
 public TestThread(String t){
     super(t);
 }
 @Override
 public void run() {
  System.out.println(getName() + " 即将进入阻塞");
 
  synchronized (obj) {
   try {
    System.out.println(getName() + " go to wait()");
    obj.wait(2);
   } catch (InterruptedException e) {
    System.out.println(getName() + " Test Thread Interrupted");
   }
  }
 
  System.out.println(getName() + " 被唤醒");
 }
 
 public void resumeByNotify() {
  synchronized (obj) {
   System.out.println(getName() + " go to notify()");
   obj.notify();
  }
 }
 
 public void resumeByNotifyAll() {
  synchronized (obj) {
   System.out.println(getName() + " go to notifyAll()");
   obj.notifyAll();
  }
 }
}
