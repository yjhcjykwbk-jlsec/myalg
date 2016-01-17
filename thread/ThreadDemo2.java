import java.util.concurrent.atomic.AtomicInteger;
/**
 * 多线程对同一个变量进行操作
 * 
 * @author pinefantasy
 * @since 2013-10-31
 */
public class ThreadDemo2 {
    private static int count = 0;
    public static class CountThread implements Runnable {// 1.这边有线程安全问题，共享变量乱套了
        @Override
        public void run() {
            for (int i = 0; i < 100; i++) {
                try {
                    Thread.sleep(50);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                count++;
                //System.out.println(Thread.currentThread().getName() + ", count = " + count);
            }
        }
    }
    private static final Object lock = new Object();// 这边使用的lock对象
    private static int lockedCount = 0;
    public static class Count2Thread implements Runnable {// 这边使用的是互斥锁方式
        @Override
        public void run() {
            synchronized (lock) {// 使用互斥锁方式处理
                for (int i = 0; i < 100; i++) {
                    lockedCount++;
                    //System.out.println(Thread.currentThread().getName() + ", count = " + lockedCount);
                }
            }
        }
    }
    private static AtomicInteger ai = new AtomicInteger();// 这边使用的是并发包的AtomicXXX类，使用的是CAS方式：compare and swap
    public static class Count3Thread implements Runnable {// AtomicInteger内部的CAS实现方式，采用的是：循环、判断、设置三部曲方式
        @Override
        public void run() {
            for (int i = 0; i < 100; i++) {
                int tmp = ai.incrementAndGet();// 采用CAS方式处理
                //System.out.println(Thread.currentThread().getName() + ", count = " + tmp);
            }
        }
    }
    private static volatile int countV = 0;// 定义成volatile，让多线程感知，因为值是放在主存中
    public static class Count4Thread implements Runnable {// volatile定义的变量只是说放到了主存，当时++操作并不是原子操作，这个要小心
        @Override
        public void run() {
            for (int i = 0; i < 100; i++) {
                try {
                    Thread.sleep(50);// 这边让线程休眠下，增加出错概率
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                countV++;// volatile要正确使用，不是说定义成volatile就是安全的，还是要注意++ --操作并不是原子操作
                //System.out.println(Thread.currentThread().getName() + ", count = " + countV);
            }
        }
    }
    /**
     * 使用泛型简单编写一个测试方法
     * 
     * @param <T>
     * @param t
     * @throws InstantiationException
     * @throws IllegalAccessException
     * @throws InterruptedException
     */
    public static <T> void testTemplate(T t) throws InstantiationException, IllegalAccessException, InterruptedException {
        for (int i = 0; i < 5; i++) {
            if (t instanceof Runnable) {
                Class<?> c = t.getClass();
                Object object = c.newInstance();
                new Thread((Runnable) object).start();
            }
        }
    }
    /**
     * <pre>
     * 1.test1 线程不安全演示例子，count变量不能得到预期的效果
     * 2.test2 在test1基础上改进的，用互斥锁sync处理
     * 3.test3 在test1基础上改进的，用AtomicInteger类来实现
     * 4.test4 有问题的方法，因为i++并不是原子操作，将count定义为volatile类型的
     * 
     * @param args
     * @throws InterruptedException
     * @throws IllegalAccessException
     * @throws InstantiationException
     */
    public static void main(String[] args) throws InterruptedException, InstantiationException, IllegalAccessException {
        // 1.测试1
        testTemplate(new CountThread());
        // 2.测试2
        testTemplate(new Count2Thread());
        // 3.测试3
        testTemplate(new Count3Thread());
        // 4.测试4
        testTemplate(new Count4Thread());
        Thread.sleep(15000);
        System.out.println(count);
	System.out.println(lockedCount);
        System.out.println(ai.get());
        System.out.println(countV);
    }
}
