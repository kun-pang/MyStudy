- 为了统一类或者方法中的类型（使用Object时，使用类型都可以传入，导致结果与预想不一致）

- 使用

	- ```java
		/* 方法中使用 */
		public void test01(){
		    System.out.println(mm("aaa")); 
		}
		
		public <T> T mm(T t1){
		    return t1;
		}
		```

	- ```java
		/* 在类中使用 */
		public void test02(){
		    A<String> s = new A<>("abc");
		    System.out.println(s.getT());
		}
		
		class A<T>{
		    private T t;
		
		    public A(T t) {
		        this.t = t;
		    }
		
		    public T getT() {
		        return t;
		    }
		}
		```

	- 上界

		- ```java
			public void test03(){
			        System.out.println(nn(10, 20)); /* 此时T的类型为Integer */
			    }
			
			/* 泛型的上界 */
			/* T只能是Number型 或者 Number的子类 */
			public <T extends Number> double nn(T t1, T t2){
			    return t1.doubleValue() + t2.doubleValue();
			}
			```

		- 

	- 下界

		- ```java
			public void test04(){
			    List<Integer> l1 = new ArrayList<>();
			    l1.add(1);
			    l1.add(2);
			    l1.add(3);
			    l1.add(4);
			
			    List<Integer> l2 = new ArrayList<>();
			    System.out.println(l1);
			    System.out.println(l2);
			    moveAll(l1, l2);
			    System.out.println(l1);
			    System.out.println(l2);
			}
			
			/* 泛型的下界 */
			/* T只能是T 或者 T的父类 */
			public <T> void moveAll(List<? extends T> src, List<? super T> dest) {
			    for (T item : src) {
			        dest.add(item);
			    }
			    src.clear();
			}
			```

		- 