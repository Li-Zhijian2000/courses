interface Inter {
	void show();
}

class Outer {
	static Inter method() {
		return new Inter() {
			@Override
			public void show() {
				System.out.println("oo");
			}
		};
	}
}

public class Test {
	public static void main(String[] args) {
		Outer.method().show();
	}
}