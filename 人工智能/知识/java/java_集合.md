## 集合出现原因

-  数组缺陷：
	- 长度一旦分配不可改变（时刻需要关注数组是否满）
	- 对里面的数据 增删操作 性能低下（顺序表，数据的移动）
	- 装的类型 都是 同一种类型

## 容器的组织关系

- ```mermaid
	graph LR
	    %% 顶层接口定义
	    Collection["Collection<br/>一个一个装元素（接口）"]
	    Map["Map<br/>一对一对的装（接口）"]
	
	    %% Collection 子接口
	    List["List<br/>元素有序且能重复（接口）"]
	    Set["Set<br/>元素无序且不能重复（接口）"]
	    Queue["Queue<br/>元素先进先出（接口）"]
	
	    %% List 实现类
	    ArrayList["ArrayList"]
	    LinkedList["LinkedList"]
	    Vector["Vector"]
	
	    %% Set 实现类
	    HashSet["HashSet"]
	    TreeSet["TreeSet"]
	
	    %% Queue 实现类
	    PriorityQueue["PriorityQueue"]
	
	    %% Map 实现类
	    HashMap["HashMap"]
	    TreeMap["TreeMap"]
	    HashTable["HashTable"]
	
	    %% Collection 体系继承关系
	    Collection --> List
	    Collection --> Set
	    Collection --> Queue
	
	    List --> ArrayList
	    List --> LinkedList
	    List --> Vector
	
	    Set --> HashSet
	    Set --> TreeSet
	
	    Queue --> PriorityQueue
	
	    %% Map 体系继承关系
	    Map --> HashMap["HashMap<br>实现"]
	    Map --> TreeMap["TreeMap<br>实现"]
	    Map --> HashTable["HashTable<br>实现"]
	
	    %% 样式美化（区分接口/实现类）
	    classDef interfaceStyle fill:#ff9999,stroke:#333,stroke-width:2px
	    classDef classStyle fill:#ffff99,stroke:#333,stroke-width:2px
	
	    class Collection,List,Set,Queue,Map interfaceStyle
	    class ArrayList,LinkedList,Vector,HashSet,TreeSet,PriorityQueue,HashMap,TreeMap,HashTable classStyle
	```

- 

- | 实现类          | 所属接口类（特点）                | 实现与核心特性                                               |
	| --------------- | --------------------------------- | ------------------------------------------------------------ |
	| `ArrayList`     | `List`（元素有序、可重复）        | 基于数组实现的 List，**查找效率高，增删效率低**              |
	| `LinkedList`    | `List`（元素有序、可重复）        | 基于链表实现的 List，**增删效率高，查找效率低**，可作为栈、队列、双端队列使用 |
	| `Vector`        | `List`（元素有序、可重复）        | 基于数组实现的 List，**线程安全**，性能低于 `ArrayList`，已逐步被淘汰 |
	| `HashSet`       | `Set`（元素无序、不可重复）       | 基于 `HashMap` 实现的 Set，**查询、增删效率极高**，不保证元素顺序 |
	| `TreeSet`       | `Set`（元素无序、不可重复）       | 基于红黑树实现的 Set，**元素自然有序 / 按自定义规则排序**，增删查效率为 `O(log n)` |
	| `PriorityQueue` | `Queue`（先进先出，按优先级区分） | 基于堆实现的优先队列，**元素按优先级排序**，不遵循严格的 FIFO |
	| `HashMap`       | `Map`（键值对存储，键唯一）       | 基于「数组 + 链表 + 红黑树（JDK8+）」实现，**查询、增删效率极高，线程不安全** |
	| `TreeMap`       | `Map`（键值对存储，键唯一）       | 基于红黑树实现的 Map，**键自然有序 / 按自定义规则排序**，线程不安全 |
	| `HashTable`     | `Map`（键值对存储，键唯一）       | 基于「数组 + 链表」实现，**线程安全**，性能远低于 `HashMap`，已逐步被淘汰 |
	
- list容器移除元素

  - 

    ```java
    /* list是顺序表 删除或者增加元素 都会改变后续元素位置 */
    
    public static void main(String[] args) {
            List<String > list = new ArrayList<>();
    
            list.add("张三");
            list.add("王五");
            list.add("张柳");
            list.add("张柳");
            list.add("张无忌");
            list.add("李星星");
            list.add("张柳");
            list.add("张柳");
    
            System.out.println(list);
            /* 倒序遍历 */
            for(int i = list.size() - 1; i >= 0; i--){
                String str = list.get(i);
                if("张柳".equals(str)){
                    list.remove(i);
                }
            }
    
            /* 使用迭代器，删除方法使用的是迭代器的删除方法 */
            Iterator<String> iterator = list.iterator();
            while (iterator.hasNext()){
                if("张柳".equals(iterator.next())){
                    iterator.remove();
                }
            }
    
            System.out.println(list);
    
        }
    ```

  - 


### ArrayList

- API

- 

- | 方法                        | 说明                                         |
	| --------------------------- | -------------------------------------------- |
	| boolean add(E e)            | 在末尾添加元素                               |
	| E get(int index)            | 通过 下标 获取元素                           |
	| int size()                  | 元素个数                                     |
	| E remove(int index)         | 根据 下标 删除元素，同时返回删除之前的元素值 |
	| boolean remove(Object o)    | 指定元素删除，遇到的第一个匹配元素进行删除   |
	| int indexOf(Object o)       | 返回第一个匹配上的元素 从前往后匹配          |
	| int lastIndexOf(Object o)   | 返回第一个匹配上的元素 从后往前匹配          |
	| E set(int index, E element) | 修改指定位置的元素 ，返回修改之前的元素值    |
	| boolean isEmpty()           | 判断是否为空                                 |
	| void clear()                | 清空                                         |

- 底层原理

	- ```java
		/* =左边父类或者接口 =右边是子类或者实现 */
		/* ArrayList()的形参是通过泛型实现，使用时需要指定具体类型 */
		public class ArrayList<E> {
		
		    /**
		     * 默认初始容量
		     */
		    private static final int DEFAULT_CAPACITY = 10;
		
		    /**
		     * 空数组实例（用于无参构造）
		     */
		    private static final Object[] DEFAULTCAPACITY_EMPTY_ELEMENTDATA = {};
		
		    /**
		     * 真正存储元素的数组（底层就是 Object 数组）
		     * 所有数据都存在这里
		     */
		    transient Object[] elementData;
		
		    /**
		     * 实际元素个数（不是数组长度！）
		     */
		    private int size;
		
		    // ===================== 构造方法 =====================
		
		    /**
		     * 无参构造：先给空数组，第一次 add 时才扩容到 10
		     */
		    public ArrayList() {
		        this.elementData = DEFAULTCAPACITY_EMPTY_ELEMENTDATA;
		    }
		
		    /**
		     * 指定初始容量构造
		     */
		    public ArrayList(int initialCapacity) {
		        if (initialCapacity > 0) {
		            this.elementData = new Object[initialCapacity];
		        } else if (initialCapacity == 0) {
		            this.elementData = new Object[0];
		        } else {
		            throw new IllegalArgumentException("Illegal Capacity: " + initialCapacity);
		        }
		    }
		
		    // ===================== 添加元素 =====================
		
		    /**
		     * 尾部添加元素
		     */
		    public boolean add(E e) {
		        // 确保容量足够，不够就扩容
		        ensureCapacityInternal(size + 1);
		        // 直接赋值
		        elementData[size++] = e;
		        return true;
		    }
		
		    /**
		     * 计算最小需要容量
		     */
		    private void ensureCapacityInternal(int minCapacity) {
		        ensureExplicitCapacity(calculateCapacity(elementData, minCapacity));
		    }
		
		    /**
		     * 计算容量：如果是空数组，返回默认容量 10
		     */
		    private static int calculateCapacity(Object[] elementData, int minCapacity) {
		        if (elementData == DEFAULTCAPACITY_EMPTY_ELEMENTDATA) {
		            return Math.max(DEFAULT_CAPACITY, minCapacity);
		        }
		        return minCapacity;
		    }
		
		    /**
		     * 判断是否需要扩容
		     */
		    private void ensureExplicitCapacity(int minCapacity) {
		        // 所需最小容量 > 当前数组长度 → 扩容
		        if (minCapacity - elementData.length > 0)
		            grow(minCapacity);
		    }
		
		    /**
		     * 扩容核心方法
		     * 新容量 = 旧容量 + 旧容量 >> 1   →  1.5 倍
		     */
		    private void grow(int minCapacity) {
		        int oldCapacity = elementData.length;
		        // 新容量 = 旧容量 * 1.5
		        int newCapacity = oldCapacity + (oldCapacity >> 1);
		
		        // 特殊情况处理
		        if (newCapacity - minCapacity < 0)
		            newCapacity = minCapacity;
		
		        // 数组拷贝，生成新数组
		        elementData = Arrays.copyOf(elementData, newCapacity);
		    }
		
		    // ===================== 获取元素 =====================
		
		    /**
		     * 根据下标获取元素
		     */
		    public E get(int index) {
		        // 检查下标是否越界
		        rangeCheck(index);
		        return (E) elementData[index];
		    }
		
		    /**
		     * 下标越界检查
		     */
		    private void rangeCheck(int index) {
		        if (index >= size)
		            throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);
		    }
		
		    // ===================== 删除元素 =====================
		
		    /**
		     * 根据下标删除
		     */
		    public E remove(int index) {
		        rangeCheck(index);
		
		        E oldValue = (E) elementData[index];
		
		        // 需要移动的元素个数
		        int numMoved = size - index - 1;
		        if (numMoved > 0)
		            // 数组拷贝，把后面元素往前挪
		            System.arraycopy(elementData, index + 1,
		                             elementData, index,
		                             numMoved);
		
		        // 最后一位置空，帮助GC回收
		        elementData[--size] = null;
		
		        return oldValue;
		    }
		
		    // ===================== 其他常用方法 =====================
		
		    /**
		     * 获取元素个数
		     */
		    public int size() {
		        return size;
		    }
		
		    /**
		     * 修改元素
		     */
		    public E set(int index, E element) {
		        rangeCheck(index);
		
		        E oldValue = (E) elementData[index];
		        elementData[index] = element;
		        return oldValue;
		    }
		
		    /**
		     * 查找元素第一次出现位置
		     */
		    public int indexOf(Object o) {
		        if (o == null) {
		            for (int i = 0; i < size; i++)
		                if (elementData[i] == null)
		                    return i;
		        } else {
		            for (int i = 0; i < size; i++)
		                if (o.equals(elementData[i]))
		                    return i;
		        }
		        return -1;
		    }
		}
		```

### LinkedList

- API

  - ArrayList的方法 LinkedList方法也全有

    -  

    - | 方法（与ArrayList相同的方法没有写出） | 说明                             |
    	| ------------------------------------- | -------------------------------- |
    	| void addFirst(E e)                    | 在头部添加新元素                 |
    	| void addLast(E e)                     | 在末尾添加新元素                 |
    	| boolean offer(E e)                    | 添加新元素到末尾                 |
    	| void push(E e)                        | 在头部添加新元素                 |
    	| boolean contains(Object o)            | 元素是否存在                     |
    	| E element()                           | 返回头部的第一个元素，不删除元素 |
    	| E getLast()                           | 获取第一个元素                   |
    	| E getFirst()                          | 获取最后一个元素                 |
    	| E peek()                              | 返回头部第一个元素,不删除元素    |
    	| E poll()                              | 返回头部第一个元素,删除元素      |
    	| E pop()                               | 返回头部第一个元素,删除元素      |

  - 底层原理

    - ```java
    	public class LinkedList<E> {
    	
    	    // 节点内部类：双向链表节点
    	    private static class Node<E> {
    	        E item;       // 数据
    	        Node<E> next; // 后继
    	        Node<E> prev; // 前驱
    	
    	        Node(Node<E> prev, E element, Node<E> next) {
    	            this.item = element;
    	            this.next = next;
    	            this.prev = prev;
    	        }
    	    }
    	
    	    // 链表头尾节点（真正的底层结构）
    	    transient Node<E> first;
    	    transient Node<E> last;
    	
    	    // 元素个数
    	    transient int size = 0;
    	
    	    public LinkedList() {}
    	
    	    // ==================== 尾插 ====================
    	    public boolean add(E e) {
    	        linkLast(e);
    	        return true;
    	    }
    	
    	    // 链接到尾部（核心）
    	    void linkLast(E e) {
    	        Node<E> l = last;
    	        // 新节点：前驱是旧last，后继null
    	        Node<E> newNode = new Node<>(l, e, null);
    	        last = newNode;
    	
    	        if (l == null)
    	            first = newNode; // 链表为空，头尾都是它
    	        else
    	            l.next = newNode; // 旧尾节点指向新节点
    	
    	        size++;
    	    }
    	
    	    // ==================== 头插 ====================
    	    public void addFirst(E e) {
    	        linkFirst(e);
    	    }
    	
    	    private void linkFirst(E e) {
    	        Node<E> f = first;
    	        Node<E> newNode = new Node<>(null, e, f);
    	        first = newNode;
    	
    	        if (f == null)
    	            last = newNode;
    	        else
    	            f.prev = newNode;
    	
    	        size++;
    	    }
    	
    	    // ==================== 尾删（核心） ====================
    	    public E removeLast() {
    	        Node<E> l = last;
    	        if (l == null)
    	            throw new NoSuchElementException();
    	        return unlinkLast(l);
    	    }
    	
    	    // 解除尾节点
    	    private E unlinkLast(Node<E> l) {
    	        E element = l.item;
    	        Node<E> prev = l.prev;
    	
    	        // 断开引用，帮助GC
    	        l.item = null;
    	        l.prev = null;
    	
    	        last = prev;
    	
    	        // 如果前驱为空，说明链表空了
    	        if (prev == null)
    	            first = null;
    	        else
    	            prev.next = null;
    	
    	        size--;
    	        return element;
    	    }
    	
    	    // ==================== 头删 ====================
    	    public E removeFirst() {
    	        Node<E> f = first;
    	        if (f == null)
    	            throw new NoSuchElementException();
    	        return unlinkFirst(f);
    	    }
    	
    	    private E unlinkFirst(Node<E> f) {
    	        E element = f.item;
    	        Node<E> next = f.next;
    	
    	        f.item = null;
    	        f.next = null;
    	
    	        first = next;
    	
    	        if (next == null)
    	            last = null;
    	        else
    	            next.prev = null;
    	
    	        size--;
    	        return element;
    	    }
    	
    	    // ==================== 大小 ====================
    	    public int size() {
    	        return size;
    	    }
    	}
    	```


### HashMap（线程不安全）

- 常用API

	- Key值唯一

	- | 方法               | 作用                     |
		| ------------------ | ------------------------ |
		| `put(k,v)`         | 添加 / 修改键值对        |
		| `get(k)`           | 根据键获取值             |
		| `remove(k)`        | 根据键删除键值对         |
		| `containsKey(k)`   | 判断是否包含某个键       |
		| `containsValue(v)` | 判断是否包含某个值       |
		| `size()`           | 获取键值对个数           |
		| `isEmpty()`        | 判断是否为空             |
		| `clear()`          | 清空所有元素             |
		| `keySet()`         | 获取所有键的集合         |
		| `entrySet()`       | 获取所有键值对对象的集合 |

	- 遍历方式

		- ```java
			/* entrySet 遍历（推荐）一次性拿到键 + 值 */
			Set<Map.Entry<String, String>> entries = hashMap.entrySet();
			for (Map.Entry<String, String> entry : entries) {
			    entry.getKey();
			    entry.getValue();
			}
			
			/*  keySet 遍历 先拿所有 key，再通过 key 找 value */
			Set<String> keySet = hashMap.keySet();
			for (String key : keySet) {
			    hashMap.get(key);
			}
			```

	- hash冲突问题

		- 不同的key通过hash函数作用后，可以会等到相同的位置
		- 解决方法
			- 链地址法（数组中存链表）
				- 链表过长，会导致cpu消耗大
			- 开放地址法（使用其他的空闲空间）
			- 再哈希法（使用多个哈希函数）
			- 建立公共溢出表

	- hashMap攻击问题（jdk8之前）

		- 在同一位置放入过多的元素（单个链表过长），然后查找，导致性能消耗大 
		- 解决方式：链表换成 红黑树

	- 红黑树代替链表）

	- 使用haspMap造出cpu 100问题（问题出现：jdk8之前 发生hash冲突的时候采用头插法）（解决：jdk8之后，就改成了尾插法）

	- put方法

		- 源码

			- ```java
				public V put(K key, V value) {
				        return putVal(hash(key), key, value, false, true); /* 具体添加/修改 是通过putVal()方法实现的 */
				}
				
				/* 添加 / 修改逻辑 */
				final V putVal(int hash, K key, V value, boolean onlyIfAbsent,
				               boolean evict) {
				    Node<K,V>[] tab; /* 临时变量 指向实际存储数据的数组table  */
				    Node<K,V> p; 
				    int n, i;
				    if ((tab = table) == null || (n = tab.length) == 0) /* table数组是否存在 存在是否为空 */
				        n = (tab = resize()).length; /* 创建数组，并获取数组的长度 */
				    /* (n - 1) & hash] ==> hash % 长度 = key对应的索引位置*/
				    if ((p = tab[i = (n - 1) & hash]) == null)  /* 该索引位置为空 */
				        tab[i] = newNode(hash, key, value, null); /* 放入新的Node对象 */
				    else { /* 该索引位置有值 */
				        Node<K,V> e; K k;
				        if (p.hash == hash &&
				            ((k = p.key) == key || (key != null && key.equals(k)))) /* 第一个的哈希值 key值 与目标一样，那就保存该对象，进行后续的修改 */
				            e = p;
				        else if (p instanceof TreeNode) /* p是树对象 */
				            e = ((TreeNode<K,V>)p).putTreeVal(this, tab, hash, key, value); /* 使用树的添加方法 */
				        else { /* p是链表 */
				            for (int binCount = 0; ; ++binCount) { 
				                if ((e = p.next) == null) { /* 找到空位，进行添加 */
				                    p.next = newNode(hash, key, value, null); /* 添加新对象 */
				                    if (binCount >= TREEIFY_THRESHOLD - 1) /* 当节点数大于 8 - 1时,进行类型转换  */
				                        treeifyBin(tab, hash); /* 将链表 转换成 红黑树 */
				                    break;
				                }
				                if (e.hash == hash &&
				                    ((k = e.key) == key || (key != null && key.equals(k)))) /* 找到与目标key一样的 元素 ，保存该对象 */
				                    break;
				                p = e; /* 移动指针 */
				            }
				        }
				        if (e != null) { /* 修改操作 当前对象不为空 */
				            V oldValue = e.value; /* 保留旧值 */
				            if (!onlyIfAbsent || oldValue == null)
				                e.value = value;
				            afterNodeAccess(e); /* 没有意义，只有其子类LinkedHashMap中才有实现 */
				            return oldValue;
				        }
				    }
				    ++modCount;
				    if (++size > threshold) /* 元素 大于 加载因子 * 初始容量; threshold在resize方法中赋初始值(Integer.MAX_VALUE —— int最大值) )  */ /* 加载因子(DEFAULT_LOAD_FACTOR) = 0.75 初始容量(DEFAULT_INITIAL_CAPACITY) = 16 */
				        resize();
				    afterNodeInsertion(evict); /* 没有意义，只有其子类LinkedHashMap中才有实现 */
				    return null;
				}
				```

			- resize() ：扩容方法；逻辑：先判断是否是第一次来 ，第一来就初始化节点数组；不是第一次来，创建更大的数组，重新计算各个元素的位置（位置= hash值 % 数组长度） ，放入新数组中。

		- 加载因子（控制扩容时机）

			- 扩容条件 = 数组长度 * 加载因子 
			- 出现原因：数组不能满了才扩大，否则会出现大量的hash冲突

		- hashcode() 和 equals()的关系【e.hash == hash && ((k = e.key) == key || (key != null && key.equals(k)))】

			- 在平时 二者无关
			- 在HashMap中，只有先确定了位置（hashcode），才能进行key值的判（equals）。在hash表中有一下关系
				- 当hashcode相等时，两对象的equals不一定相等
				- 当hashcode不相等时，两对象的equals一定不相等
			- 了解
				- hashcode()的实现 
					1. **Object.hashCode () = 地址相关**
					2. **String、Integer、自定义类 = 按内容算 hashCode**
					3. **因为 int 范围有限，不同对象必然可能算出相同 hashCode**（hashCode的返回值时int型）


### HashSet

- 基于 HashMap 进行实现的
	- 使用了HashMap中的key，其中Vuale没有使用
	- 所以使用自定义的类型作为类型时，应该 **重写Object的hashcode()  和 equals()**

### Hashtable 

- 传入键-值对
- 使用synchronized进行加锁（因为这个，所以后续不怎么使用）
- 用法与HashMap一样
- 与HashMap区别
	- HashMap线程不安全，性能高；Hashtable线程安全，性能低
	- HashMap的Key 和 Value都是可以是null，Hashtable的Key 和Value都不能是null
	- HashMap的父类 ：AbstractMap； Hashtable的父类：Dictionary（字典类）

### Properties

- 父类是Hashtable
- 本质上是 properties文件【键值对文件】在内存上的体现
- Collections : 是集合的工具类

### 其余

- 对象的排序

	- TreeSet 与 TreeMap 中添加的元素必须是能比较大小的，如果不能直接比较大小，需要通过下面两种方式告知 比较规则

		1. 让传入的元素类 实现Comparable 接口，重写compareTo方法

			- ```java
				public class User implements Comparable{
				    @Override
				    public int compareTo(Object o) {
				        if(this == o) {return 0;}
				        if(o instanceof User){
				            return this.id - ((User) o).id;
				        }
				        return 0;
				    }
				}
				
				```

		2. 写一个比较器  实现 Comparator 接口  ，重写compare 方法

			- ```java
				public class UserComparator implements Comparator {
				
				    public UserComparator() {}
				
				    @Override
				    public int compare(Object o1, Object o2) {
				        if(o1 instanceof User && o2 instanceof User){ 
				            return ((User) o2).getId() - ((User) o1).getId(); /* 需要进行类型判断 */
				        }
				        return 0;
				    }
				}
				
				```

	- TreeMap是通过 Key值来进行排序的

## 迭代器

- 统一遍历不同容器的方式，每种容器上都有一个方法 ，该方法用来获取这个

- 使用

	- ```java
		/* 获取容器的迭代器 */ Iterator<String> iterator = 容器遍历名.iterator();
		        while(iterator.hasNext()){
		            System.out.println(iterator.next());
		        }
		
		/* 第二种 增强的for  */
		for (String s : list) {
		    System.out.println(s);
		}
		```

- 实现

	- ```java
		/* 内部类实现方式 */
		package demo.day05.iterator;
		
		import java.util.Iterator;
		
		public class MyLinkedList {
		    /* 节点类 */
		    private class Node{
		        Object data;
		        Node next;  /* 后驱节点 */
		        Node prev; /* 前驱节点 */
		
		        public Node(Object data, Node next, Node prev) {
		            this.data = data;
		            this.next = next;
		            this.prev = prev;
		        }
		    }
		
		    private Node first;
		    private Node last;
		
		    private int size; /* 元素个数 */
		
		    /* 构造器 */
		    public MyLinkedList(){
		        this.first = null;
		        this.last = null;
		        this.size = 0;
		    }
		
		    /* 返回元素个数 */
		    public int size(){
		        return this.size;
		    }
		
		    /* 添加 头插 */
		    public void addFirst(Object o){
		        Node f = first; /* 头部节点 */
		        Node newNode = new Node(o,f,null);
		        first = newNode;
		        if(f == null){
		            last = newNode;
		        }else{
		            f.prev = newNode;
		        }
		        this.size++;
		    }
		
		    /* 添加 尾插 */
		    public void addLast(Object o){
		        Node l = last; /* 头部节点 */
		        Node newNode = new Node(o,null,l);
		        last = newNode;
		        if(l == null){
		            first = newNode;
		        }else{
		            l.next = newNode;
		        }
		        this.size++;
		    }
		
		    /* 查询 */
		    public int indexOf(Object o){
		        Node node = first;
		        if(node == null){
		            return -1;
		        }
		
		        for(int i = 0; i < size; i++){
		            if(node.data.equals(o)){
		                return i;
		            }
		            node = node.next;
		        }
		        return -1;
		    }
		
		    /* 查询元素是否存在 */
		    public boolean contains(Object o){
		        return indexOf(o) != -1;
		    }
		
		    /* 删除元素 尾删 */
		    public Object removeLast(){
		        Node l = null;
		        if(last == null){
		            return null;
		        }else if(last.prev == null){
		            l = last;
		            last = l.prev;
		            first = null;
		        }else {
		            l = last;
		            last = l.prev; /* 指向前一个元素 */
		            last.next = null;
		        }
		        l.next = null;
		        l.prev = null;
		        size--;
		        return l.data;
		    }
		
		    /* 删除 头删 */
		    public Object removeFirst(){
		        Node f = null;
		        if(first == null){
		            return null;
		        }else if(first.next == null){
		            f = first;
		            first = f.next;
		            last = null;
		        } else{
		            f = first;
		            first = f.next;
		            first.prev = null;
		        }
		        f.next = null;
		        f.prev = null;
		        size--;
		        return f.data;
		    }
		
		    /* 重写toString */
		    @Override
		    public String toString() {
		        StringBuffer sb = new StringBuffer();
		        Node node = this.first;
		        sb.append("[");
		        for(int i = 0; i < size; i++){
		            sb.append(node.data);
		            node = node.next;
		            if(i != size - 1){
		                sb.append(",");
		            }
		        }
		        sb.append("]");
		        return sb.toString();
		    }
		
		    /* 迭代器接口 */
		    public MyIterato iterato(){
		        return new MyIterato();
		    }
		
		    /* 创建迭代器 -- 内部类 */
		    /* 实现接口Iterator */
		    private class MyIterato implements Iterator {
		        private Node node;
		
		        public MyIterato(){
		            this.node = first;
		        }
		
		        @Override
		        public boolean hasNext() {
		            return node != null;
		        }
		
		        @Override
		        public Object next() {
		            Object data = null;
		            if(hasNext() != false){
		                data = node.data;
		                node = node.next;
		            }
		            return data;
		        }
		    }
		
		
		}
		
		
		package demo.day05.iterator;
		
		import org.junit.Test;
		
		import java.util.ArrayList;
		import java.util.Iterator;
		
		public class TestMyIterator {
		
		
		    @Test
		    public void test(){
		       MyLinkedList m1 = new MyLinkedList();
		       m1.addFirst("a");
		       m1.addFirst("b");
		       m1.addFirst("c");
		       m1.addFirst("d");
		
		        System.out.println(m1);
		
		       Iterator iterato = m1.iterato();
		       while(iterato.hasNext()){
		           System.out.println(iterato.next());
		       }
		
		    }
		}
		
		```

	