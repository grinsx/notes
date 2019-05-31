# Service 服务

[TOC]

# 1. 介绍
​	Service（服务）是一个没有用户界面的在后台运行执行耗时操作的应用组件。其他应用组件能够启动Service，
​	并且当用户切换到另外的应用场景，Service将持续在后台运行。另外，一个组件能够绑定到一个service与之交互（IPC机制），
​	例如，一个service可能会处理网络操作，播放音乐，操作文件I/O或者与内容提供者（content provider）交互，
​	所有这些活动都是在后台进行。Service有两种状态，“启动的”和“绑定”

	通过startService()启动的服务处于“启动的”状态，一旦启动，service就在后台运行，即使启动它的应用组件已经被销毁了。
	通常started状态的service执行单任务并且不返回任何结果给启动者。比如当下载或上传一个文件，
	当这项操作完成时，service应该停止它本身。
	
	还有一种“绑定”状态的service，通过调用bindService()来启动，一个绑定的service提供一个允许组件与service交互的接口，
	可以发送请求、获取返回结果，还可以通过跨进程通信来交互（IPC）。绑定的service只有当应用组件绑定后才能运行，
	多个组件可以绑定一个service，当调用unbind()方法时，这个service就会被销毁了。
	另外，在官方的说明文档中还有一个警告：
		service与activity一样都存在与当前进程的主线程中，所以，一些阻塞UI的操作，比如耗时操作不能放在service里进行，
		比如另外开启一个线程来处理诸如网络请求的耗时操作。如果在service里进行一些耗CPU和耗时操作，可能会引发ANR警告，
		这时应用会弹出是强制关闭还是等待的对话框。所以，对service的理解就是和activity平级的，只不过是看不见的，
		在后台运行的一个组件，这也是为什么和activity同被说为Android的基本组件。

**注意**

- 服务(Service)是Android中实现后台运行的解决方案,它非常适合去执行那些不需要和用户交互而且还长期运行的任务.
- 不过需要注意的是,服务并不是运行在一个独立的进程当中,而是依赖于创建服务时所在的应用程序进程.当某个应用程序进程被杀掉时,所有依赖于该进程的服务也会停止运行.
- 另外,也不要被服务的后台概念所迷惑,实际上服务并不会自动开启线程,所有的代码都是**默认运行在主线程中的**.也就是说,我们需要在服务的内部手动创建子线程,并在这里执行具体的任务,否则就有可能出现**主线程被阻塞住**的情况.
- **实际上每个服务都只会存在一个实例**.

# 2. 开启服务
 	Services can be started with Context.startService() and Context.bindService(). 

# 3. 停止服务

	stopService(stopIntent);

# 4. start方式开启服务的特点(面试)

> 服务是在后台运行的 可以理解成是没有界面的Activity
定义四大组件的方式都是一样的,都需要在清单文件中注册(动态广播其实不需要在清单文件中注册)
定义一个类继承自Service

特点:

(1) 服务通过startService()方式开启,第一次开启服务,会执行服务的onCreate()方法和nStartCommand()方法

(2) 如果第二次再点击按钮开启服务,服务之后执行onStartCommand()方法

(3) 服务被开启后,会在设置界面的running里面找得到这个服务

<font size="5" color="#ff0000"> (4) startService开启服务,服务就会在后台长期运行,直到用户手工停止,或者调用stopService()方法,或者是杀APP进程(至少在国产手机上是这样),服务才会被销毁.</font>

# 5. bindService   方式开启服务的特点(面试)
​		(1) 当点击按钮第一次开启服务,会依次执行服务的onCreate()方法->onBind()方法
​		(2) 当第二次点击按钮再调用bindService(),服务没有响应
<font size="5" color="#ff0000">(3) 当Activity销毁的时候服务也销毁,不求同时生但求同时死</font>

		(4) 通过bind方法开启服务,服务不能在设置页面里面找到,相当于一个隐形的服务(高大上)
		(5) bindService不能多次解绑,多次解绑会报错

# 6. 可以使用Service开启特殊的广播接收者
​		1.比如屏幕的解锁     这种广播不能在清单文件中注册,注册了也没用,需要在代码中动态的注册.   这时候可以使用服务注册,
​		注册之后,即使Activity被onDestroy()服务依然在,广播依然可以监听到屏幕的状态.

# 7. bindService方式调用服务里面方法的过程

1. 定义一个服务,继承自Service,需要在清单文件中注册.服务里面有一个方法需要Activity去调用.

		//测试方法
	​	public void banzheng(int money){
	​		if(money > 100){
	​			Toast.makeText(getApplicationContext(), "我是领导,把证给你办了", Toast.LENGTH_SHORT).show();
	​		} else {
	​			Toast.makeText(getApplicationContext(), "就这点儿钱,还想办事", Toast.LENGTH_SHORT).show();
	​		}
	​	}
2. 定义一个中间人对象(MyBinder)继承自Binder
	​	
		public class MyBinder extends Binder{
	​		//2.定义一个方法    调用上面的测试方法
	​		public void callbanzheng(int money){
	​			banzheng(money);
	​		}
	​	}
3. 在服务里面的onBind()方法里面,把我们定义的中间人对象(MyBinder)返回
	​	
		public IBinder onBind(Intent intent) {
	​		//3.把定义的中间人对象返回
	​		return new MyBinder();
	​	}
4. 在Activity的onCreate()方法里面调用bindService()绑定服务,需要一个类继承自ServiceConnection来监听服务的状态,监听的时候可以拿到服务通过onBind()方法返回的Binder对象.  (记得在Activity的onDestroy()方法中unbindService()解除绑定)

		//开启服务 
	​	Intent intent = new Intent(this,TestService.class);
	​	//连接服务 TestService
	​	myConn = new MyConn();
	​	//绑定服务 
	​	bindService(intent, myConn, BIND_AUTO_CREATE);

		//监视服务的状态
		class MyConn implements ServiceConnection{
	
			//当连接服务成功后
			@Override
			public void onServiceConnected(ComponentName name, IBinder service) {
				////[4]获取我们定义的中间人对象
				myBinder = (MyBinder) service;
			}
		
			//失去连接
			@Override
			public void onServiceDisconnected(ComponentName name) {
				
			}
			
		}

5. 拿到中间人(服务通过onBind()方法返回的Binder对象),就可以间接的调用服务里面的方法了.

		@Override
	​	public void onClick(View v) {
	​		//通过我们定义的中间人对象 间接调用服务里面的方法
	​		myBinder.callbanzheng(1002);
	​	}

# 8. 通过接口方式调用服务里面的方法

> 接口可以隐藏代码内部的细节,让程序员暴露自己只想暴露的方法

6. 定义一个接口把想暴露的方法都定义在接口里面
7. 定义的中间人对象,实现定义的接口

    private class MyBinder extends Binder implements IService{
    ​		//2.定义一个方法    调用上面的测试方法
    ​		public void callbanzheng(int money){
    ​			banzheng(money);
    ​		}
    ​		

    		public void callDaMaJiang(){
    			daMaJiang();
    		}
    	
    		public void callXiSangNa(){
    			xiSangNa();
    		}
    		
    	}
8. 再获取我们定义的中间人对象方式变量

    //当连接服务成功后
    ​	@Override
    ​	public void onServiceConnected(ComponentName name, IBinder service) {
    ​		

    		//[4]获取我们定义的中间人对象 
    		myBinder = (Iservice) service;
    	}
    # 9. 混合方式 开启服务
> 需求:既想让服务在后台长期运行,也想调服务里面的方法.(eg:网易云音乐,在后台能播放音乐,应该是用服务实现的,然后也能在后台切换上一曲下一曲,应该也能调用服务里面的方法).   这时候需要混合方式开启服务

1. 先调用startService()方法,保证服务在后台长期运行.
2. 调用bindService()目的获取我们定义的中间人对象(写一个内部类继承Binder,通过onBind()方法返回),调用服务里面的方法.
3. unbindService()
4. 最后调用stopService()停止服务

# 10. aidl介绍
> 1.远程服务,运行在其他应用里面的服务<br/>
> 2.本地服务,运行在自己应用里面的服务<br/>
> 3.进行进程间通信  IPC<br/>
> 4.aidl Android interface Defination Language Android接口定义语言,专门用来解决,进程间通信的.<br/>

## aidl 实现步骤和之前调用服务里面的方法的区别
- 先把Iservice.java文件后缀改成aidl文件
- aidl不认识public,把这个文件里面的public关键字去掉
- 会自动生成一个Stub类,实现IPC(进程间通信)
- 我们定义的中间人对象(Service里面)直接继承自Stub
- 想要保证2个应用程序的aidl文件是同一个,要求aidl所在包名要相同.(把另外一个应用里面的aidl文件复制一份到自己的应用中,放到和另一个应用的相同的包名下面.)
- 获取中间人对象,Stub.asinterface(IBinder obj);这是静态方法,在监听服务的状态类实现ServiceConnection时,onServiceConnected()可以用得到.

## aidl的应用场景
支付宝   非常有名    支付的方法 


# 11. Activity与Service进行通信

1. 首先在Service里面新建一个类继承自Binder,

	private DownloadBinder mBinder = new DownloadBinder();

    class DownloadBinder extends Binder{
   ​     /**
   ​      * 模拟的下载资源的方法
   ​      */
   ​     public void startDownload(){
   ​         Log.i(TAG, "startDownload: executed");
   ​     }

        /**
         * 模拟的下载资源时的获取下载进度的方法
         * @return
         */
        public int getProgress(){
            Log.i(TAG, "getProgress: executed");
            return 0;
        }

    }

2. 然后重写Service类里面的onBind()方法,返回创建出来的DownloadBinder对象

3. 在Activity中新建一个服务里面Binder类的实例.

		private MyService.DownloadBinder downloadBinder;
	
		/**
		 * 监听服务的连接状态
		 */
		private ServiceConnection connection = new ServiceConnection() {
		    @Override
		    public void onServiceConnected(ComponentName name, IBinder service) {
		        Log.i(TAG, "onServiceConnected: 连接上服务");
		        //成功绑定服务时调用
		        downloadBinder = (MyService.DownloadBinder)service;
		        downloadBinder.startDownload();
		        downloadBinder.getProgress();
		    }
		
		    @Override
		    public void onServiceDisconnected(ComponentName name) {
		        //断开连接
		        Log.i(TAG, "onServiceDisconnected: 断开连接");
		    }
		};

4. 绑定服务

		//绑定服务
    ​    //参数:Intent,ServiceConnection实例,flag     这里是BIND_AUTO_CREATE表示绑定后自动创建服务
    ​    bindService(intent,connection,BIND_AUTO_CREATE);

5. 解绑服务
   ​             
		unbindService(connection);

# 12. 使用	前台进程

> 服务的系统优先级还是比较低的,当系统出现内存不足的情况时,就有可能会回收掉正在后台运行的服务.如果你希望服务可以一直保持运行的状态,而不会由于系统内存不足的原因导致被回收,就可以考虑使用前台进程.

> 前台服务和普通服务的罪的的区别就在于,它会一直有一个正在运行的图标在系统的状态栏显示.

	@Override
	public void onCreate() {
	    super.onCreate();
	
	    //设置当前Service为前台服务
	    Intent intent = new Intent(this, MainActivity.class);
	    PendingIntent pendingIntent = PendingIntent.getActivity(this,0,intent,0);
	    Notification notification = new NotificationCompat.Builder(this)
	            .setContentTitle("This is content title")  //设置标题
	            .setContentText("this is content text")   //设置内容
	            .setWhen(System.currentTimeMillis())      //设置时间
	            .setSmallIcon(R.mipmap.ic_launcher)     //设置状态栏小图标
	            .setLargeIcon(BitmapFactory.decodeResource(getResources(),R.mipmap.ic_launcher)) //大图标
	            .setContentIntent(pendingIntent)  //设置点击时跳转事件
	            .build();  //创建
	    startForeground(1,notification);   //开始前台服务    让MyService变成一个前台服务,并在状态栏显示出来
	}

# 13. IntentService

> 为了可以简单地创建一个异步的,会自动停止的服务,Android专门提供了一个IntentService类.

> 运行结束后会自动停止

> 集开启线程和自动停止于一身.

	public class MyIntentService extends IntentService {
	
	    private final static String TAG = "MyIntentService";
	
	    public MyIntentService() {
	        super("MyIntentService");  //调用父类的有参构造函数
	    }
	
	    //这个方法是在子线程中运行    一般在这里处理一些具体的逻辑,不用担心ANR问题
	    @Override
	    protected void onHandleIntent(Intent intent) {
	        Log.i(TAG, "onHandleIntent: 当前线程"+Thread.currentThread().getId());
	        if (intent != null) {
	        }
	    }
	
	    //根据IntentService的特性,在服务运行结束后会自动停止的
	    @Override
	    public void onDestroy() {
			//这是在主线程
	        Log.i(TAG, "onDestroy: ");
	        super.onDestroy();
	    }
	}

开启IntentService

	 Intent intentService = new Intent(this, MyIntentService.class);
	            startService(intentService);

