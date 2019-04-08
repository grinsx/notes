> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 https://www.jianshu.com/p/550a8bd71214

本文是 [《Android Jetpack 官方架构组件》](https://blog.csdn.net/mq2553299/column/info/24151) 系列的最后一篇文章，和一些朋友的观点不同的是，我认为它是 **最重要** 的核心组件，因为 `LiveData`本身很简单，但其代表却正是 **MVVM** 模式最重要的思想，即 **数据驱动视图**（也有叫观察者模式、响应式等）——这也是摆脱 **顺序性编程思维** 的重要一步。

本文默认读者已经学习了 **Lifecycle** , 欢迎关注笔者的 Jetpack 系列：

> **争取打造 AndroidLi Jetpack 讲解的最好的博客系列**：
> 
> *   [Android 官方架构组件 Lifecycle：生命周期组件详解 & 原理分析](https://www.jianshu.com/p/b1208012b268)
> *   [Android 官方架构组件 ViewModel: 从前世今生到追本溯源](https://www.jianshu.com/p/59adff59ed29)
> *   [Android 官方架构组件 LiveData: 观察者模式领域二三事](https://www.jianshu.com/p/550a8bd71214)
> *   [Android 官方架构组件 Paging：分页库的设计美学](https://www.jianshu.com/p/10bf4bf59122)
> *   [Android 官方架构组件 Navigation：大巧不工的 Fragment 管理框架](https://www.jianshu.com/p/ad040aab0e66)

> **Android Jetpack 实战篇**：
> 
> *   [开源项目：MVVM+Jetpack 实现的 Github 客户端](https://github.com/qingmei2/MVVM-Rhine)
> *   [总结：使用 MVVM 尝试开发 Github 客户端及对编程的一些思考](https://www.jianshu.com/p/b03710f19123)

### 回顾 LiveData：从处境尴尬到咸鱼翻身

我们都知道 Google 在去年的 I/O 大会非常隆重地推出了一系列的 **架构组件**，本文的主角，[LiveData](https://developer.android.com/topic/libraries/architecture/livedata) 正是其中之一，和`Lifecycle`、`ViewModel`、`Room`比较起来，`LiveData`可以说是最受关注的组件也不为过，遗憾的是，在发布的最初，关注点是因为它饱含争议，相当一部分的开发者认为——`LiveData` 实在太 **鸡肋** 了！

2017 年的 `Android` 技术领域，`RxJava`无疑是炙手可热的名词之一，其 **观察者模式** 和 **链式调用** 所表现出来的 API 优秀地设计，使得它位于很多 Android 项目技术选型中的 **第一序列**。

这时 Google 隆重推出了具有类似功能的 `LiveData` （其本质就是观察者模式），可以说是有点初生牛犊不怕虎的感觉，开发者们不由自主将`LiveData` 和 `RxJava` 进行了对比，结论基本出奇的一致—— `LiveData`所提供的功能，`RxJava`完全足以胜任，而后者却同时具有庞大的生态圈，这是`LiveData`短时间内难以撼动（替代）的。

时至今日，`LiveData`的使用者越来越多，最主要的原因当然和 Google 的强力支持不无关系，但是`LiveData`本身优秀的设计和轻量级也吸引了越来越多开发者的青睐。

现在我们需要去了解它了，我们都知道，`LiveData` 本质是 **观察者模式** 的体现，可关键的问题是：

### 观察者模式到底是啥？！

讨论这个问题之前，我们先看看 `LiveData` 的用法，这实在没什么技术难度，比如，你可以这样实例化一个`LiveData`并使用它：

![](https://upload-images.jianshu.io/upload_images/7293029-7a3648acd36fd8d9.png)

如你所见，`LiveData`实际上就像一个 **容器**, 本文中它存储了一个`String`类型的引用，每当这个容器内 `String`的数据发生变化，我们都能在回调函数中进行对应的处理，比如 **Toast**。

这似乎和我们日常用到的 `Button` 控件的 `setOnClickListener()` 非常相似，实际上点击事件的监听也正是 **观察者模式** 的一种体现，对于观察者来说，它并不关心观察对象 **数据是如何过来的**，而只关心数据过来后 **进行怎样的处理**。

这也就是说，**事件发射的上游** 和 **接收事件的下游** 互不干涉，大幅降低了互相持有的依赖关系所带来的强耦合性。

**我依然坚持学习原理比学习如何应用的优先级更高**，因此我们先来一一探究`LiveData`本身设计中存在的那些闪光点背后的故事。

### LiveData 是如何避免内存泄漏的

我们都知道，`RxJava`在使用过程中，**避免内存泄漏**是一个不可忽视的问题，因此我们一般需要借助三方库比如`RxLifecycle`、`AutoDispose`来解决这个问题。

而反观`LiveData`，当它被我们的`Activity`订阅观察，这之后`Activity`如果`finish()`掉，`LiveData`本身会自动 “清理” 以避免内存泄漏。

这是一个非常好用的特性，它的实现原理非常简单，其本质就是利用了 Jetpack 架构组件中的另外一个成员—— **Lifecycle**。

让我们来看看`LiveData`被订阅时内部的代码：

![](https://upload-images.jianshu.io/upload_images/7293029-17d1a94464d77842.png)

源码中的逻辑非常复杂，我们只关注核心代码：

*   1\. 首先我们在调用`LiveData.observer()`方法时，传递的第一个参数`Acitivity`实际被向上抽象成为了 `LifecycleOwner`，第二个参数`Obserser`实际就是我们的观察后的回调。

> 这里我们需要注意的是，执行`LiveData.observer()`方法时 **必须处于主线程**，否则会因为断言失败而抛出异常。

*   2\. 方法内部实际上将我们传入的 2 个参数包装成了一个新的 `LifecycleBoundObserver`对象，它实现了 **Lifecycle** 组件中的`LifecycleObserver`接口:

![](https://upload-images.jianshu.io/upload_images/7293029-7de0a52d619e6faf.png)

这里就解释了为什么`LiveData`能够 **自动解除订阅而避免内存泄漏** 了，因为它内部能够感应到`Activity`或者`Fragment`的生命周期。

这种设计非常巧妙——在我们初识 **Lifecycle** 组件时，总是下意识认为它能够对大的对象进行有效生命周期的管理（比如 **Presenter**），实际上，这种生命周期的管理我们完全可以应用到各个功能的基础组件中，比如大到吃内存的 **MediaPlayer**（多媒体播放器）、绘制设计复杂的 **自定义 View**，小到随处可见的`LiveData`，都可以通过实现`LifecycleObserver`接口达到 **感应生命周期并内部释放重的资源** 的目的。

> 关于上述代码中注释了 **更新 LiveData 的活跃状态** 的源码，我们先跳过，稍后我们会详细探讨它。

*   1.  我们继续回到上上一个源码片段的第三步中，对于一个可观察的`LiveData`来讲，当然存在多个观察者同时订阅观察的情况，因此考虑到这一点，Google 的工程师们为每一个`LiveData`配置了一个`Map`存储所有的观察者。
*   4\. 到了这一步，我们将第 2 步包装生成的对象交给我们传入的 `Activity`，让它在不同的生命周期事件中去逐一通知其所有的观察者，当然也包含了我们的`LiveData`。

### 数据更新后如何通知到回调方法？

`LiveData`原生的 API 提供了 2 种方式供开发者更新数据, 分别是 `setValue()`和`postValue()`，官方文档明确标明：`setValue()`方法必须在 **主线程** 进行调用，而`postValue()`方法更适合在执行较重工作 **子线程** 中进行调用（比如网络请求等）——在所有情况下，调用`setValue()`或`postValue()`都会 **触发观察者并更新 UI**。

**柿子挑软的捏**，我们先看`setValue()`方法的实现原理：

![](https://upload-images.jianshu.io/upload_images/7293029-74c6e7a696797624.png)

通过保留最终的核心代码，我们很清晰了解了`setValue()`方法为什么能更新`LiveData`的值，并且通知到回调函数中的代码去执行，比如更新 UI。

但是我们知道，**普遍情况下，Android 不允许在子线程更新 UI**，但是`postValue()`方法却可以在子线程更新`LiveData()`的数据，并通知更新 UI，这是如何实现的呢？

其实答案已经呼之欲出了，就是通过 `Handler`：

![](https://upload-images.jianshu.io/upload_images/7293029-6b954b58ac4c80cc.png)

**现在你已经对`LiveData`整体了一个基本的了解了**，接下来让我们开始去探究更细节的闪光点。

### 看完源码，你告诉我才算入门？

`LiveData`本身非常简单，毕竟它本身的源码一共也就 500 行左右，也许你要说 **准备面试粗读一遍源码就够了**，很遗憾，即使是粗读了源码，也很难说能够完全招架更深入的提问...

让我们来看一道题目：在下述 Activity 完整的生命周期中，`Activity`一共观察到了几次数据的变更——即 **一共打印了几条 Log** ？（补充纠正，onStop() 方法中值应该为 "onStop"）

![](https://upload-images.jianshu.io/upload_images/7293029-fdd5f8bdfd312795.png)

公布答案：

![](https://upload-images.jianshu.io/upload_images/7293029-b4dfbe14343002d0.png)

意外的是，`livedata.observer()`的本次观察并没有观察到 **onCreate**、**onStop** 和 **onDestroy** 的数据变更。

#### 为什么会这样？

还记得上文提到过 2 次的 **LiveData 的活跃状态 (Active)** 相关代码吗？实际上，`LiveData`内部存储的每一个`LifecycleBoundObserver`本身都有`shouldBeActive`的状态：

![](https://upload-images.jianshu.io/upload_images/7293029-fcacf53831ee49bf.png)

现在我们明白了，原来并不是只要在`onDestroy()`之前为`LiveData`进行更新操作，`LiveData`的观察者就能响应到对应的事件的。

虽然我们明白了这一点，但是如果更深入的思考，你会又多一个问题，那就是：

*   既然`LiveData`已经能够实现在`onDestroy()`的生命周期时自动解除订阅，为什么还要多此一举设置一个`Active`的状态呢？

仔细想想，其实也不难得到答案，`Activity`并非只有`onDestroy()`一种状态的，更多时候，新的`Activity`运行在栈顶，旧的`Activity`就会运行在 `background`——这时旧的`Activity`会执行对应的`onPause()`和`onStop()`方法，我们当然不会关心运行在后台的`Activity`所观察的`LiveData`对象（即使数据更新了，我们也无从进行对应 UI 的更新操作），因此`LiveData`进入 **InActive(待定、非活跃)** 状态，`return`并且不去执行对应的回调方法，是 **非常缜密的优秀设计** 。

当然，有同学提出，我如果希望这种情况下，`Activity`在后台依然能够响应数据的变更，可不可以呢？当然可以，`LiveData`此外还提供了`observerForever()`方法，在这种情况下，它能够响应到任何生命周期中数据的变更事件：

![](https://upload-images.jianshu.io/upload_images/7293029-10eb57c69097d8c3.png)

除此之外，源码中处处都是优秀的细节，比如对于`observe()`方法和`observerForever()`方法对应生成的包装类，后者方法生成的是`AlwaysActiveObserver`对象，统一抽象为`ObserverWrapper`。

![](https://upload-images.jianshu.io/upload_images/7293029-672cb362278ea5ff.png)

这种即使只有 2 种不同场景，也通过代码的设计，将公共业务进行向上抽离为抽象类的严谨，也非常值得我们学习。

## 小结，与更深入的思考

本来写了更多，篇幅所限，最终还是决定删除了相当一部分和 `RxJava` 有关的内容，这些内容并非是将 `LiveData` 和 `RxJava` 进行对比一决高下—— 例如，Google 官方提供了 `LiveData` 和 `RxJava` 互相进行转换的工具类：

[https://developer.android.com/reference/android/arch/lifecycle/LiveDataReactiveStreams](https://developer.android.com/reference/android/arch/lifecycle/LiveDataReactiveStreams)

值得玩味的是，官方的工具类中，`LiveData`向`RxJava`的转换方法，返回值并非是一个`Flowable`，而是一个`Publisher`接口：

![](https://upload-images.jianshu.io/upload_images/7293029-3bbb4282701b1118.png)

正如我在注释中标注的，这个工具方法返回的是一个接口，很大程度上限制了我们对`RxJava`众多强大操作符的使用，**这是否是来自 Google 的恶意**？

当然不是，对于这种行为，我的理解是 Google 对于`LiveData`本身严格的约束——它只应该用于进行数据的观察，而不是花哨的操作；转换为 Flowable 当然非常简单，但是这种行为是否属于`LiveData`本身职责的逾越，更准确来说，是否属于**不必要的过度设计**？这些是我们需要去细细揣度的。

**我无从验证我的理解是否正确**，但是我的这个理由已经足够说服我自己，再往下已不再是`LiveData`的范畴，关于这一点我将会专门起一篇文章去进行更深入的探讨，欢迎关注。

**-------------------------- 广告分割线 ------------------------------**

## 关于我

Hello，我是[却把清梅嗅](https://github.com/qingmei2)，如果您觉得文章对您有价值，欢迎 ❤️，也欢迎关注我的[博客](https://www.jianshu.com/u/df76f81fe3ff)或者 [Github](https://github.com/qingmei2)。

如果您觉得文章还差了那么点东西，也请通过**关注**督促我写出更好的文章——万一哪天我进步了呢？

*   [我的 Android 学习体系](https://github.com/qingmei2/android-programming-profile)
*   [关于文章纠错](https://github.com/qingmei2/Programming-life/blob/master/error_collection.md)
*   [关于知识付费](https://github.com/qingmei2/Programming-life/blob/master/appreciation.md)