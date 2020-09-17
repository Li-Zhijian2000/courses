class ThreadPrint {
    final private static Object LOCK = new Object();

    private boolean flag = true;

    public void num() {
        int j = 1, count = 26;
        while (count > 0) {
            synchronized(LOCK) {
                try {
                    if (flag) {
                        System.out.format("%d%d", j, j + 1);
                        count--;
                        j += 2;
                        flag = false;
                        LOCK.notify();
                    } else {
                        LOCK.wait();
                    }
                } catch (InterruptedException e) {
                    System.out.println(e.getStackTrace());
                }                
            }
        }

    }

    public void alpha() {
        char ch = 'A';
        int count = 26;
        while (count > 0) {
            synchronized(LOCK) {
                try {
                    if (flag) {
                        LOCK.wait();
                    } else {
                        System.out.format("%c ", ch);
                        count--;
                        ch++;
                        flag = true;
                        LOCK.notify();
                    }
                } catch (InterruptedException e) {
                    System.out.println(e.getStackTrace());
                }
            }
        }
    }

    public static void main(String[] args) {
        ThreadPrint tp = new ThreadPrint();
        new Thread(() -> tp.alpha()).start();
        new Thread(() -> tp.num()).start();

        try {
            Thread.sleep(100);
            System.out.println();
        } catch (InterruptedException e) {
            System.out.println(e.getStackTrace());
        }
    }
}
