public class PV {

    private int i = 0;
    private boolean ok = false;

    private final Object LOCK = new Object();

    public boolean P(int count) {
        synchronized (LOCK) {
            try {
                if (ok) {
                    LOCK.wait();
                } else {
                    i++;
                    System.out.println("P: " + i);
                    ok = true;
                    LOCK.notify();
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            return i == count ? false : true;
        }
    }

    public boolean V(int count) {
        synchronized (LOCK) {
            try {
                if (ok) {
                    System.out.println("V: " + i);
                    ok = false;
                    LOCK.notify();
                } else {
                    if (i == count) return false;
                    LOCK.wait();
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            return true;
        }
    }

    public static void main(String[] args) {
        PV pv = new PV();
        int count = 10;

        new Thread(() -> {
            while (pv.P(count))
                ;
        }).start();

        new Thread(() -> {
            while (pv.V(count))
                ;
        }).start();

        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}