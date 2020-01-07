> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 https://juejin.im/post/5bce688e6fb9a05cf715d1c2

原文地址: https://juejin.im/post/5bce688e6fb9a05cf715d1c2

以下是 **骚年你的屏幕适配方式该升级了!** 系列文章，欢迎转发以及分享:

*   [骚年你的屏幕适配方式该升级了!（一）- 今日头条适配方案](https://juejin.im/post/5b7a29736fb9a019d53e7ee2)
*   [骚年你的屏幕适配方式该升级了!（二）-smallestWidth 限定符适配方案](https://juejin.im/post/5ba197e46fb9a05d0b142c62)
*   [今日头条屏幕适配方案终极版正式发布!](https://juejin.im/post/5bce688e6fb9a05cf715d1c2)

扫描或点击以下二维码，加入技术交流 QQ 群 455850365

[![](https://user-gold-cdn.xitu.io/2018/10/30/166c39d6ff062b92?imageView2/0/w/1280/h/960/format/webp/ignore-error/1)](https://link.juejin.im?target=https%3A%2F%2Fshang.qq.com%2Fwpa%2Fqunwpa%3Fidkey%3Dab3be932171c71fefc36a8a05f972d0ddfc80dd1e47e91db9eab9da65b4e86e7)

前言
==

我在前面两篇文章中详细介绍了 [今日头条适配方案](https://juejin.im/post/5b7a29736fb9a019d53e7ee2) 和 [SmallestWidth 限定符适配方案](https://juejin.im/post/5ba197e46fb9a05d0b142c62) 的原理，并验证了它们的可行性，以及总结了它们各自的优缺点，可以说这两个方案都是目前比较优秀、比较主流的 **Android** 屏幕适配方案，而且它们都已经拥有了一定的用户基数

但是对于一些才接触这两个方案的朋友，肯定或多或少还是不知道如何选择这两个方案，我虽然在之前的文章中给出了它们各自的优缺点，但是并没有用统一的标准对它们进行更细致的对比，所以也就没办法更形象的体现它们的优劣，那下面我就用统一的标准对它们进行对比，看看它们的对比情况

方案对比
====

我始终坚定地认为在这两个方案中，并不能以单个标准就能评判出谁一定比谁好，因为它们都有各自的优缺点，都不是完美的，从更客观的角度来看，它们谁都不能成为最好的那个，只有可能明确了它们各自的优缺点，知道在它们的优缺点里什么是我能接受的，什么是我不能接受的，是否能为了某些优点做出某些妥协，从而选择出一个最适合自己项目的屏幕适配方案

单纯的争论谁是最好的 **Android** 屏幕适配方案没有任何意义，每个人的需求不一样，站的角度不一样，评判标准也不一样，你能接受的东西他不一定能接受，你觉得不可接受的东西他却觉得可以接受，你有你的理由，他有他的理由，想让一个观点让所有人都能接受太难了！所以我在这里只是列出它们的对比项和对比结果，尽可能的做到客观，最后的选择结果请自行决定，如果还有什么遗漏的对比项，请补充！

| 对比项目 | 对比对象 A | 对比结果 | 对比对象 B |
| --- | --- | --- | --- |
| 适配效果 (越高越好) | 今日头条适配方案 | ≈ | SW 限定符适配方案 (在未覆盖的机型上会存在一定的误差) |
| 稳定性 (越高越好) | 今日头条适配方案 | < | SW 限定符适配方案 |
| 灵活性 (越高越好) | 今日头条适配方案 | > | SW 限定符适配方案 |
| 扩展性 (越高越好) | 今日头条适配方案 | > | SW 限定符适配方案 |
| 侵入性 (越低越好) | 今日头条适配方案 | < | SW 限定符适配方案 |
| 使用成本 (越低越好) | 今日头条适配方案 | < | SW 限定符适配方案 |
| 维护成本 (越低越好) | 今日头条适配方案 | < | SW 限定符适配方案 |
| 性能损耗 | 今日头条适配方案没有性能损耗 | = | SW 限定符适配方案没有性能损耗 |
| 副作用 | 今日头条适配方案会影响一些三方库和系统控件 | ≈ | SW 限定符适配方案会影响 App 的体积 |

可以看到 **SmallestWidth 限定符适配方案** 和 **今日头条适配方案** 的适配效果其实都是差不多的，我在前面的文章中也通过公式计算过它们的精确度，**SmallestWidth 限定符适配方案** 运行在未覆盖的机型上虽然也可以适配，但是却会出现一定的误差，所以 **今日头条适配方案** 的适配精确度确实要比 **SmallestWidth 限定符适配方案** 略高的，不过只要 **SmallestWidth 限定符适配方案** 合理的分配资源文件，适配效果的差距应该也不大

**SmallestWidth 限定符适配方案** 主打的是稳定性，在运行过程中极少会出现安全隐患，适配范围也可控，不会产生其他未知的影响，而 **今日头条适配方案** 主打的是降低开发成本、提高开发效率，使用上更灵活，也能满足更多的扩展需求，简单一句话概括就是，这两兄弟，一个求稳，一个求快，好了，我就介绍这么多了，自己选择吧！

AndroidAutoSize
===============

![](https://user-gold-cdn.xitu.io/2018/10/23/1669f70f1fc2e5e5?imageView2/0/w/1280/h/960/format/webp/ignore-error/1)

由来
--

下面就开始介绍我根据 **今日头条屏幕适配方案** 优化的屏幕适配框架 [**AndroidAutoSize**](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2FJessYanCoding%2FAndroidAutoSize)，大家千万不要认为，我推出的屏幕适配框架 [**AndroidAutoSize**](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2FJessYanCoding%2FAndroidAutoSize) 是根据 **今日头条屏幕适配方案** 优化的，我本人就一定支持 **今日头条屏幕适配方案** 是最好的 **Android** 屏幕适配方案这个观点，它确实很优秀，但同样也有很多不足，我最真实的观点在上面就已经表述咯，至于我为什么要根据 **今日头条屏幕适配方案** 再封装一个屏幕适配框架，无外乎就以下几点原因:

*   **SmallestWidth 限定符适配方案** 已经有多个优秀的开源解决方案了，它们已经能满足我们日常开发中的所有需求
    
*   **今日头条** 官方技术团队只公布了 **今日头条屏幕适配方案** 的 [文章](https://link.juejin.im?target=https%3A%2F%2Fmp.weixin.qq.com%2Fs%2Fd9QCoBP6kV9VSWvVldVVwA) 以及核心代码，但并没有在 **Github** 上创建公开的仓库，一个新的方案必定要有一个成长迭代的过程，在此期间，一定需要一个可以把所有使用者聚集起来的公共社区，可以让所有使用该方案的使用者在上面交流，大家一起总结、一起填坑，这样才能让该方案更成熟稳定，这就是开源的力量
    
*   **今日头条** 官方技术团队公布的核心代码并不能满足我的所有需求，已经开源的其他基于 **今日头条屏幕适配方案** 的开源项目以及解决方案也不能满足我的所有需求，而我有更好的实现想法
    
*   [MVPArms](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2FJessYanCoding%2FMVPArms) 需要一个适配效果还不错并且切换维护成本也比较低的屏幕适配框架，以帮助使用者用较低的成本、工作量将已经停止维护的 **AndroidAutoLayout** 快速替换掉
    

我建议大家都可以去实际体验一下 **今日头条屏幕适配方案** 和 **SmallestWidth 限定符适配方案**，感受下它们的异同，我给的建议是，可以在项目中先使用 **今日头条屏幕适配方案**，感受下它的使用方式以及适配效果，**今日头条屏幕适配方案** 的侵入性非常低，如果在使用过程中遇到什么不能解决的问题，马上可以切换为其他的屏幕适配方案，在切换的过程中也花费不了多少工作量，试错成本非常低

但如果你在项目中先使用 **SmallestWidth 限定符适配方案**，之后在使用的过程中再遇到什么不能解决的问题，这时想切换为其他的屏幕适配方案，这工作量可就大了，每个 **Layout** 文件都含有大量的 **dimens** 引用，改起来这工作量得有多大，想想都觉得后怕，这就是侵入性太高导致的最致命的问题

如果想体验 **今日头条屏幕适配方案**，千万不要错过 **AndroidAutoSize** 哦！仅需一步即可接入项目，下面是 **AndroidAutoSize** 的地址:

> Github : [您的 Star 是我坚持的动力 ✊](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2FJessYanCoding%2FAndroidAutoSize)

### 与今日头条屏幕适配方案的关系

**AndroidAutoSize** 与 **今日头条屏幕适配方案** 的关系，相当于汽车和发动机的关系，**今日头条屏幕适配方案** 官方公布的代码，只实现了修改系统 **density** 的相关逻辑，这的确在屏幕适配中起到了最关键的作用，但这还远远还不够

要想让使用者能够更傻瓜式的使用该方案，并且能够应对日常开发中的所有复杂需求，那在架构框架时，还需要考虑 **API** 的易用性以及合理性、框架的扩展性以及灵活性、功能的全面性、注释和文档的易读性等多个方面的问题

于是我带着我的这些标准在网上搜寻了很久，发现并没有任何一个开源框架或解决方案能够达到我的所有标准，它们大多数还只是停留在将 **今日头条屏幕适配方案** 封装成工具类来引入项目的阶段，这样在功能的扩展上有限制，并且对用户的使用体验也不好，而我想做的是一个全面性的产品级屏幕适配框架，这离我最初的构想，差距还非常大，于是我只好自己动手，将我的所有思想实现，这才有了 **AndroidAutoSize**

写完 **AndroidAutoSize** 框架后，因为对 **今日头条屏幕适配方案** 有了更加深入的理解，所以才写了 [骚年你的屏幕适配方式该升级了!（一）- 今日头条适配方案](https://juejin.im/post/5b7a29736fb9a019d53e7ee2)，以帮助大家更清晰的理解 **今日头条屏幕适配方案**

### 与 AndroidAutoLayout 的关系

**AndroidAutoSize** 因为名字和 **鸿神** 的 **AndroidAutoLayout** 非常相似，并且在填写设计图尺寸的方式上也极为相似，再加上我写的屏幕适配系列的文章也发布在了 **鸿神** 的公众号上，所以很多人以为 **AndroidAutoSize** 是 **鸿神** 写的 **AndroidAutoLayout** 的升级版，这里我哭笑不得 😂，我只好在这里说一句，大家好，我叫 [JessYan](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2FJessYanCoding)，的确可以理解为 **AndroidAutoSize** 是 **AndroidAutoLayout** 的升级版，但是它是我写的，关注一波呗

但 **AndroidAutoSize** 和 **AndroidAutoLayout** 的原理，却天差地别，比如 **AndroidAutoLayout** 只能使用 **px** 作为布局单位，而 **AndroidAutoSize** 恰好相反，在布局中 **dp、sp、pt、in、mm** 所有的单位都能支持，唯独不支持 **px**，但这也意味着 **AndroidAutoSize** 和 **AndroidAutoLayout** 在项目中可以共存，互不影响，所以使用 **AndroidAutoLayout** 的老项目也可以放心的引入 **AndroidAutoSize**，慢慢的完成屏幕适配框架的切换

之所以将框架取名为 **AndroidAutoSize**，第一，是想致敬 **AndroidAutoLayout** 对 **Android** 屏幕适配领域的贡献，第二，也想成为在 **Android** 屏幕适配领域有重要影响力的框架

结构
--

我在上面就已经说了很多开源框架以及解决方案，只是把 **今日头条屏幕适配方案** 简单的封装成一个工具类然后引入项目，这时很多人就会说了 **今日头条屏幕适配方案** 官方公布的全部代码都只有 **30** 行不到，你不把它封装成工具类，那封装成什么？该怎么封装？下面就来看看 **AndroidAutoSize** 的整体结构

```
├── external
│   ├── ExternalAdaptInfo.java
│   ├── ExternalAdaptManager.java
│── internal
│   ├── CancelAdapt.java
│   ├── CustomAdapt.java
│── unit
│   ├── Subunits.java
│   ├── UnitsManager.java
│── utils
│   ├── AutoSizeUtils.java
│   ├── LogUtils.java
│   ├── Preconditions.java
│   ├── ScreenUtils.java
├── ActivityLifecycleCallbacksImpl.java
├── AutoAdaptStrategy.java
├── AutoSize.java
├── AutoSizeConfig.java
├── DefaultAutoAdaptStrategy.java
├── DisplayMetricsInfo.java
├── FragmentLifecycleCallbacksImpl.java
├── InitProvider.java
复制代码

```

**AndroidAutoSize** 根据 **今日头条屏幕适配方案** 官方公布的 **30** 行不到的代码，经过不断的优化和扩展，发展成了现在拥有 **18** 个类文件，上千行代码的全面性屏幕适配框架，在迭代的过程中完善和优化了很多功能，相比 **今日头条屏幕适配方案** 官方公布的原始代码，**AndroidAutoSize** 更加稳定、更加易用、更加强大，欢迎阅读源码，注释非常详细哦！

功能介绍
----

**AndroidAutoSize** 在使用上非常简单，只需要填写设计图尺寸这一步即可接入项目，但需要注意的是，**AndroidAutoSize** 有两种类型的布局单位可以选择，一个是 **主单位 (dp、sp)**，一个是 **副单位 (pt、in、mm)**，两种单位面向的应用场景都有不同，也都有各自的优缺点

*   **主单位**: 使用 **dp、sp** 为单位进行布局，侵入性最低，会影响其他三方库页面、三方库控件以及系统控件的布局效果，但 **AndroidAutoSize** 也通过这个特性，使用 **ExternalAdaptManager** 实现了在不修改三方库源码的情况下适配三方库的功能
    
*   **副单位**: 使用 **pt、in、mm** 为单位进行布局，侵入性高，对老项目的支持比较好，不会影响其他三方库页面、三方库控件以及系统控件的布局效果，可以彻底的屏蔽修改 **density** 所造成的所有未知和已知问题，但这样 **AndroidAutoSize** 也就无法对三方库进行适配
    

大家可以根据自己的应用场景在 **主单位** 和 **副单位** 中选择一个作为布局单位，建议想引入老项目并且注重稳定性的人群使用 **副单位**，只是想试试本框架，随时可能切换为其他屏幕适配方案的人群使用 **主单位**

其实 **AndroidAutoSize** 可以同时支持 **主单位** 和 **副单位**，但 **AndroidAutoSize** 可以同时支持 **主单位** 和 **副单位** 的目的，只是为了让使用者可以在 **主单位** 和 **副单位** 之间灵活切换，因为切换单位的工作量可能非常巨大，不能立即完成，但领导又要求马上打包上线，这时就可以起到一个很好的过渡作用

主单位
---

**主单位** 的 **Demo** 在 [demo](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2FJessYanCoding%2FAndroidAutoSize%2Fblob%2Fmaster%2Fdemo)

### 基本使用

将 **AndroidAutoSize** 引入项目后，只要在 **app** 的 **AndroidManifest.xml** 中填写上设计图尺寸，无需其他过多配置 (如果你没有其他自定义需求的话)，**AndroidAutoSize** 即可自动运行，像下面这样👇

```
<manifest>
    <application>            
        <meta-data
            android:
            android:value="360"/>
        <meta-data
            android:
            android:value="640"/>           
     </application>           
</manifest>
复制代码

```

在使用主单位时，`design_width_in_dp` 和 `design_height_in_dp` 的单位必须是 **dp**，如果设计师给你的设计图，只标注了 **px** 尺寸 (现在已经有很多 **UI** 工具可以自动标注 **dp** 尺寸了)，那请自行根据公式 **dp = px / (DPI / 160)** 将 **px** 尺寸转换为 **dp** 尺寸，如果你不知道 **DPI** 是多少？那请以自己测试机的 **DPI** 为准，如果连怎么得到设备的 **DPI** 都不知道？百度吧好伐，如果你实在找不到设备的 **DPI** 那就直接将 **px** 尺寸除以 **3** 或者 **2** 也是可以的

**如果你只是想使用 AndroidAutoSize 的基础功能，AndroidAutoSize 的使用方法在这里就结束了，只需要上面这一步，即可帮助你以最简单的方式接入 AndroidAutoSize，但是作为一个全面性的屏幕适配框架，在保证基础功能的简易性的同时，也必须保证复杂的需求也能在框架内被解决，从而达到一个小闭环，所以下面介绍的内容全是前人踩坑踩出来的一些必备功能，如果你没这个需求，或者觉得麻烦，可以按需查看或者跳过，下面的内容建议和 Demo 配合起来阅读，效果更佳**

#### 注意事项

*   你在 **AndroidManifest.xml** 中怎么把设计图的 **px** 尺寸转换为 **dp** 尺寸，那在布局时，每个控件的大小也需要以同样的方式将设计图上标注的 **px** 尺寸转换为 **dp** 尺寸，千万不要在 **AndroidManifest.xml** 中填写的是 **dp** 尺寸，却在布局中继续填写设计图上标注的 **px** 尺寸
    
*   `design_width_in_dp` 和 `design_height_in_dp` 虽然都需要填写，但是 **AndroidAutoSize** 只会将高度和宽度其中的一个作为基准进行适配，一方作为基准，另一方就会变为备用，默认以宽度为基准进行适配，可以通过 **AutoSizeConfig#setBaseOnWidth(Boolean)** 不停的切换，这意味着最后运行到设备上的布局效果，在高度和宽度中只有一方可以和设计图上一模一样，另外一方会和设计图出现偏差，为什么不像 **AndroidAutoLayout** 一样，高和宽都以设计图的效果等比例完美呈现呢？这也很简单，你无法保证所有设备的高宽比例都和你设计图上的高宽比例一致，特别是在现在全面屏全面推出的情况下，如果这里不这样做的话，当你的项目运行在与设计图高宽比例不一致的设备上时，布局会出现严重的变形，这个几率非常大，详情请看 [这里](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2FJessYanCoding%2FAndroidAutoSize%2Fissues%2F8)
    

### 自动运行是如何做到的？

很多人有疑惑，为什么使用者只需要在 **AndroidManifest.xml** 中填写一下 **meta-data** 标签，其他什么都不做，**AndroidAutoSize** 就能自动运行，并在 **App** 启动时自动解析 **AndroidManifest.xml** 中填写的设计图尺寸，这里很多人不敢相信，问我真的只需要填写下设计图尺寸框架就可以正常运行吗？难道使用了什么 **黑科技**?

其实这里并没有用到什么 **黑科技**，原理反而非常简单，只需要声明一个 **ContentProvider**，在它的 **onCreate** 方法中启动框架即可，在 **App** 启动时，系统会在 **App** 的主进程中自动实例化你声明的这个 **ContentProvider**，并调用它的 **onCreate** 方法，执行时机比 **Application#onCreate** 还靠前，可以做一些初始化的工作，**get** 到了吗？

这里需要注意的是，如果你的项目拥有多进程，系统只会在主进程中实例化一个你声明的 **ContentProvider**，并不会在其他非主进程中实例化 **ContentProvider**，如果在当前进程中 **ContentProvider** 没有被实例化，那 **ContentProvider#onCreate** 就不会被调用，你的初始化代码在当前进程中也就不会执行，这时就需要在 **Application#onCreate** 中调用下 **ContentProvider#query** 执行一下查询操作，这时 **ContentProvider** 就会在当前进程中实例化 (每个进程中只会保证有一个实例)，所以应用到框架中就是，如果你需要在多个进程中都进行屏幕适配，那就需要在 **Application#onCreate** 中调用 **AutoSize#initCompatMultiProcess** 方法

### 进阶使用

虽然 **AndroidAutoSize** 不需要其他过多的配置，只需要在 **AndroidManifest.xml** 中填写下设计图尺寸就能正常运行，但 **AndroidAutoSize** 还是为大家准备了很多可配置选项，尽最大可能满足大家日常开发中的所有扩展需求

所有的全局配置选项在 [Demo](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2FJessYanCoding%2FAndroidAutoSize%2Fblob%2Fmaster%2Fdemo%2Fsrc%2Fmain%2Fjava%2Fme%2Fjessyan%2Fautosize%2Fdemo%2FBaseApplication.java%23L55) 中都有介绍，每个 **API** 中也都有详细的注释，在这里就不过多介绍了

#### 自定义 Activity

在 **AndroidManifest.xml** 中填写的设计图尺寸，是整个项目的全局设计图尺寸，但是如果某些 **Activity** 页面由于某些原因，设计师单独出图，这个页面的设计图尺寸和在 **AndroidManifest.xml** 中填写的设计图尺寸不一样该怎么办呢？不要急，**AndroidAutoSize** 已经为你考虑好了，让这个页面的 **Activity** 实现 **CustomAdapt** 接口即可实现你的需求，**CustomAdapt** 接口的第一个方法可以修改当前页面的设计图尺寸，第二个方法可以切换当前页面的适配基准，下面的注释都解释的很清楚

```
public class CustomAdaptActivity extends AppCompatActivity implements CustomAdapt {

	 /**
     * 是否按照宽度进行等比例适配 (为了保证在高宽比不同的屏幕上也能正常适配, 所以只能在宽度和高度之中选择一个作为基准进行适配)
     *
     * @return {@code true} 为按照宽度进行适配, {@code false} 为按照高度进行适配
     */
    @Override
    public boolean isBaseOnWidth() {
        return false;
    }

	 /**
     * 这里使用 iPhone 的设计图, iPhone 的设计图尺寸为 750px * 1334px, 高换算成 dp 为 667 (1334px / 2 = 667dp)
     * <p>
     * 返回设计图上的设计尺寸, 单位 dp
     * {@link #getSizeInDp} 须配合 {@link #isBaseOnWidth()} 使用, 规则如下:
     * 如果 {@link #isBaseOnWidth()} 返回 {@code true}, {@link #getSizeInDp} 则应该返回设计图的总宽度
     * 如果 {@link #isBaseOnWidth()} 返回 {@code false}, {@link #getSizeInDp} 则应该返回设计图的总高度
     * 如果您不需要自定义设计图上的设计尺寸, 想继续使用在 AndroidManifest 中填写的设计图尺寸, {@link #getSizeInDp} 则返回 {@code 0}
     *
     * @return 设计图上的设计尺寸, 单位 dp
     */
    @Override
    public float getSizeInDp() {
        return 667;
    }
}
复制代码

```

如果某个 **Activity** 想放弃适配，让这个 **Activity** 实现 **CancelAdapt** 接口即可，比如修改 **density** 影响到了老项目中的某些 **Activity** 页面的布局效果，这时就可以让这个 **Activity** 实现 **CancelAdapt** 接口

```
public class CancelAdaptActivity extends AppCompatActivity implements CancelAdapt {

}
复制代码

```

#### 自定义 Fragment

**Fragment** 的自定义方式和 **Activity** 是一样的，只不过在使用前需要先在 **App** 初始化时开启对 **Fragment** 的支持

```
AutoSizeConfig.getInstance().setCustomFragment(true);
复制代码

```

实现 **CustomAdapt**

```
public class CustomAdaptFragment extends Fragment implements CustomAdapt {

    @Override
    public boolean isBaseOnWidth() {
        return false;
    }

    @Override
    public float getSizeInDp() {
        return 667;
    }
}
复制代码

```

实现 **CancelAdapt**

```
public class CancelAdaptFragment extends Fragment implements CancelAdapt {

}
复制代码

```

#### 适配三方库页面

在使用主单位时可以使用 **ExternalAdaptManager** 来实现在不修改三方库源码的情况下，适配三方库的所有页面 (**Activity、Fragment**)

由于 **AndroidAutoSize** 要求需要自定义适配参数或取消适配的页面必须实现 **CustomAdapt**、**CancelAdapt**，这时问题就来了，三方库是通过远程依赖的，我们无法修改它的源码，这时我们怎么让三方库的页面也能实现自定义适配参数或取消适配呢？别急，这个需求 **AndroidAutoSize** 也已经为你考虑好了，当然不会让你将三方库下载到本地然后改源码！

*   通过 **ExternalAdaptManager#addExternalAdaptInfoOfActivity(Class, ExternalAdaptInfo)** 将需要自定义的类和自定义适配参数添加进方法即可替代实现 **CustomAdapt** 的方式，[这里](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2FJessYanCoding%2FAndroidAutoSize%2Fblob%2Fmaster%2Fdemo%2Fsrc%2Fmain%2Fjava%2Fme%2Fjessyan%2Fautosize%2Fdemo%2FBaseApplication.java%23L105) 展示了使用方式，以及详细的注释
    
*   通过 **ExternalAdaptManager#addCancelAdaptOfActivity(Class)** 将需要取消适配的类添加进方法即可替代实现 **CancelAdapt** 的方式，[这里](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2FJessYanCoding%2FAndroidAutoSize%2Fblob%2Fmaster%2Fdemo%2Fsrc%2Fmain%2Fjava%2Fme%2Fjessyan%2Fautosize%2Fdemo%2FBaseApplication.java%23L94) 也展示了使用方式，以及详细的注释
    

需要注意的是 **ExternalAdaptManager** 的方法虽然可以添加任何类，但是只能支持 **Activity、Fragment**，并且 **ExternalAdaptManager** 是支持链式调用的，以便于持续添加多个页面

当然 **ExternalAdaptManager** 不仅可以对三方库的页面使用，也可以让自己项目中的 **Activity、Fragment** 不用实现 **CustomAdapt**、**CancelAdapt** 即可达到自定义适配参数和取消适配的功能

副单位
---

前面已经介绍了 **副单位** 的应用场景，这里就直接介绍 **副单位** 如何使用，**副单位** 的 **Demo** 在 [demo-subunits](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2FJessYanCoding%2FAndroidAutoSize%2Fblob%2Fmaster%2Fdemo-subunits)

### 基本使用

首先和 **主单位** 一样也需要先在 **app** 的 **AndroidManifest.xml** 中填写上设计图尺寸，但和 **主单位** 不一样的是，当在使用 **副单位** 时 `design_width_in_dp` 和 `design_height_in_dp` 的单位不需要一定是 **dp**，可以直接填写设计图的 **px** 尺寸，在布局文件中每个控件的大小也可以直接填写设计图上标注的 **px** 尺寸，无需再将 **px** 转换为 **dp**，这是 **副单位的** 特性之一，可以帮助大家提高开发效率

```
<manifest>
    <application>            
        <meta-data
            android:
            android:value="1080"/>
        <meta-data
            android:
            android:value="1920"/>           
     </application>           
</manifest>
复制代码

```

由于 **AndroidAutoSize** 提供了 **pt、in、mm** 三种类型的 **副单位** 供使用者选择，所以在使用 **副单位** 时，还需要在 **APP** 初始化时，通过 **UnitsManager#setSupportSubunits(Subunits)** 方法选择一个你喜欢的副单位，然后在布局文件中使用这个副单位进行布局，三种类型的副单位，其实效果都是一样，大家按喜欢的名字选择即可

由于使用副单位是为了彻底屏蔽修改 **density** 所造成的对三方库页面、三方库控件以及系统控件的布局效果的影响，所以在使用副单位时建议调用 **UnitsManager#setSupportDP(false)** 和 **UnitsManager#setSupportSP(false)**，关闭 **AndroidAutoSize** 对 **dp** 和 **sp** 的支持，**AndroidAutoSize** 为什么不在使用 **副单位** 时默认关闭对 **dp**、**sp** 的支持？因为允许同时支持 **主单位** 和 **副单位** 可以帮助使用者在 **主单位** 和 **副单位** 之间切换时更好的过渡，这点在前面就已经提到过

**UnitsManager** 的详细使用方法，在 [demo-subunits](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2FJessYanCoding%2FAndroidAutoSize%2Fblob%2Fmaster%2Fdemo-subunits%2Fsrc%2Fmain%2Fjava%2Fme%2Fjessyan%2Fautosize%2Fdemo%2Fsubunits%2FBaseApplication.java%23L73) 中都有展示，注释也十分详细

### 自定义 **Activity** 和 **Fragment**

在使用 **副单位** 时自定义 **Activity** 和 **Fragment** 的方式是和 **主单位** 是一样的，这里就不再过多介绍了

### 适配三方库页面

如果你的项目在使用 **副单位** 并且关闭了对 **主单位 (dp、sp)** 的支持，这时 **ExternalAdaptManager** 对三方库的页面是不起作用的，只对自己项目中的页面起作用，除非三方库的页面也使用了副单位 **(pt、in、mm)** 进行布局

其实 **副单位** 之所以能彻底屏蔽修改 **density** 所造成的对三方库页面、三方库控件以及系统控件的布局效果的影响，就是因为三方库页面、三方库控件以及系统控件基本上使用的都是 **dp、sp** 进行布局，所以只要 **AndroidAutoSize** 关闭了对 **dp、sp** 的支持，转而使用 **副单位** 进行布局，就能彻底屏蔽修改 **density** 所造成的对三方库页面、三方库控件以及系统控件的布局效果的影响

但这也同样意味着使用 **副单位** 就不能适配三方库的页面了，**ExternalAdaptManager** 也就对三方库的页面不起作用了

布局实时预览
------

在开发阶段布局时的实时预览是一个很重要的环节，很多情况下 **Android Studio** 提供的默认预览设备并不能完全展示我们的设计图，所以我们就需要自己创建模拟设备，**dp、pt、in、mm** 这四种单位的模拟设备创建方法请看 [这里](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2FJessYanCoding%2FAndroidAutoSize%2Fblob%2Fmaster%2FREADME-zh.md%23preview)

总结
==

[**AndroidAutoSize**](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2FJessYanCoding%2FAndroidAutoSize) 在经历了 **240+ commit**、**60+ issues**、**6 个版本** 的洗礼后，逐渐的稳定了下来，已经在上个星期发布了首个正式版，在这里要感谢将 **AndroidAutoSize** 接入到自己项目中的上千个使用者，感谢他们的信赖，**AndroidAutoSize** 创建的初衷就是为了让所有使用 **今日头条屏幕适配方案** 的使用者能有一个可以一起交流、沟通的聚集地，所以后面也会持续的收集并解决 [今日头条屏幕适配方案的常见问题](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2FJessYanCoding%2FAndroidAutoSize%2Fissues%2F13)，让 **今日头条屏幕适配方案** 变得更加成熟、稳定

至此本系列的第三篇文章也就完结了，这也预示着这个系列连载的终结，这篇文章建议结合系列的第一篇文章 [骚年你的屏幕适配方式该升级了!（一）- 今日头条适配方案](https://juejin.im/post/5b7a29736fb9a019d53e7ee2) 一起看，这样可以对 **今日头条屏幕适配方案** 有一个更深入的理解，如果你能将整个系列的文章都全部认真看完，那你对 **Android** 屏幕适配领域的相关知识绝对会有一个飞速的提升!

当你的项目需要切换某个框架时，你会怎么去考察、分析、对比现有的开源方案，并有足够的理由去选择或优化一个最适合自己项目的方案呢？其实整个系列文章可以看作是我怎么去选择同类型开源方案的过程，你以后当遇到同样的选择也可以参照我的思维方式去处理，当然如果以后面试官问到你屏幕适配相关的问题，你能将我如何选择、分析、对比已有方案的过程以及文章中的核心知识点告诉给面试官，那肯定比你直接说一句我使用的是某某开源库有价值得多

公众号
---

扫码关注我的公众号 JessYan，一起学习进步，如果框架有更新，我也会在公众号上第一时间通知大家

![](https://user-gold-cdn.xitu.io/2019/2/25/1692228ad4606cd8?imageView2/0/w/1280/h/960/format/webp/ignore-error/1)

以下是 **骚年你的屏幕适配方式该升级了!** 系列文章，欢迎转发以及分享:

*   [骚年你的屏幕适配方式该升级了!（一）- 今日头条适配方案](https://juejin.im/post/5b7a29736fb9a019d53e7ee2)
*   [骚年你的屏幕适配方式该升级了!（二）-smallestWidth 限定符适配方案](https://juejin.im/post/5ba197e46fb9a05d0b142c62)
*   [今日头条屏幕适配方案终极版正式发布!](https://juejin.im/post/5bce688e6fb9a05cf715d1c2)

**Hello 我叫 JessYan，如果您喜欢我的文章，可以在以下平台关注我**

*   个人主页: [jessyan.me](https://link.juejin.im?target=http%3A%2F%2Fjessyan.me)
*   GitHub: [github.com/JessYanCodi…](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2FJessYanCoding)
*   掘金: [juejin.im/user/57a9db…](https://juejin.im/user/57a9dbd9165abd0061714613)
*   简书: [www.jianshu.com/u/1d0c0bc63…](https://link.juejin.im?target=http%3A%2F%2Fwww.jianshu.com%2Fu%2F1d0c0bc634db)
*   微博: [weibo.com/u/178626251…](https://link.juejin.im?target=http%3A%2F%2Fweibo.com%2Fu%2F1786262517)

-- The end