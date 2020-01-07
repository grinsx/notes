> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 https://mp.weixin.qq.com/s?__biz=MzIxNjc0ODExMA==&mid=2247486358&idx=1&sn=4c96a908e108e55949e8b68a13d957b7&chksm=978512b7a0f29ba127826cdc07909ce4843f857e891cee34516a91a14872211c8437c4bd5335&scene=21#wechat_redirect ![](https://mmbiz.qpic.cn/mmbiz_jpg/liaczD18OicSxoMtD3tE09ETuiaoibCQklKMj4wic4Clecd8C4VGSgFjXpNAuGtzS3o7GnqzOa9iafBx03rLibKpDaMVA/640?wx_fmt=jpeg)

![](https://mmbiz.qpic.cn/mmbiz_png/liaczD18OicSwIgGwqImEF6tKibiclPDdFDicFUJLy46JTF5TsFvVqygbfC2rm0bCALTCCdSzkrl3baDbJywPOuJzMg/640?wx_fmt=png)

一. Android Q 的一项适配
------------------

Android Q 在今年 Q3 就准备发布正式版了，但有一个影响 90% 应用的适配改动。

目前，不少 Android App 都有一个启动界面（Launch/Splash Screen），即应用启动时，在显示主页前增加一个有内容的页面，这好像变成了 App 的标配。

这种设计，最初是解决冷启动时，会有白屏或黑屏的闪动问题，其目的是为了提高用户体验。

后来发现在这个过程中，不干点什么好像有点浪费，那不如拿来初始化数据、SDK，再加载个广告吧，总之，启动页承载的业务越来越多了。

在用户的角度，可以看见的就是，App 启动时，先有个启动页，在启动页加载了一个广告，倒数 3、2、1，倒数归零后跳到真实的主页。这种情况下，启动页就承载了加载广告的逻辑。通常的代码实现是在广告显示后，增加一个倒数的定时器，在倒数归零的时候，再去调用 `startActivity()` 跳转到真实的主页上。

有兴趣可以试试，不少 App 在启动后，立即按 Home 键，过 3s（广告时间？） 之后又会被调起来。

本来呢，这种设计也是无伤大雅的，但是 Android Q 来了，就不一样了。最近刚发布了 Android Q Beta 4 版本，按照其时间表来看，今年第三个季度就会发布正式版。

![](https://mmbiz.qpic.cn/mmbiz_png/liaczD18OicSwIgGwqImEF6tKibiclPDdFDicmTr4n4HTgBicmbYcZsc6SXOqKdFLpKvWlaANW00sYOZsLmOAbicTHpPg/640?wx_fmt=png)

Android Q 具有更强的隐私保护，其中有一条，它开始限制后台 App 启动 Activity。

以最新的 Android Q Beta 4 来举例，当你的 App 处于后台时，一旦尝试开启新的页面，会发生什么呢？首先你的新页面肯定是打不开的，在现有的 Beta 版本上，系统还会输出一条警告 Log，并弹出一条 Toast。

例如，我们开发者比较常用的 掘金 App。

![](https://mmbiz.qpic.cn/mmbiz_gif/liaczD18OicSwIgGwqImEF6tKibiclPDdFDicD4Btibzb04snURicxehwicmq79nfSDRH471dSTIiauiaJtfhOJvpTFUPCgw/640?wx_fmt=gif)

猜想，在正式版发布时，应该会去掉此 Toast 警告，没必要以这么强的提示来提醒用户。

但是这依然是我们需要提前做好适配准备的。毕竟在不少快速迭代的项目中，启动速度并不是优先考虑优化的指标，各种初始化也很随意的就放在了启动页里，到最后不得不优化的时候，就比较费时和令人头疼了。

二. MD 设计里的启动页
-------------

在启动页里，做大量的逻辑，甚至强制间隔几秒（显示广告），这种做法本身在 Google 的设计规范就是不推荐的，不少海外大厂的 App，也是遵循此设计规范。

![](https://mmbiz.qpic.cn/mmbiz_png/liaczD18OicSwIgGwqImEF6tKibiclPDdFDicBfCFo2jNWPRzdbfxxOp7NlgCty9459S7CrLgiazt95IB4JzRkqoe0icg/640?wx_fmt=png)

而国内的 App 里，在启动页里加塞点功能，好像是一种更为普遍的做法。

在 Material Design 的设计规范中，也明确定义了启动图的设计规范，其核心就是为了解决冷启动时，那个短暂的白屏不至于显得太突兀，设计的好了，还可以增加品牌的辨识度。

启动页面的设计，其重点在于，它仅仅在应用启动的瞬间显示，也就是说，启动页面不应该导致应用的启动变慢，强制显示一段时间广告，更是不应该的做法。

毕竟打开 App 是为了它的功能，更快把首屏展示给用户，体验就更好。

三. Q 的后台启动建议
------------

在 Android Q 之前的版本中，本质上就已经对一些页面的显示做了限制，例如 Android 8.0 增加了悬浮窗权限，其实更多的也是为了不让一些恶意的 App 打扰用户。

这次 Android Q 更彻底，当前处在后台的 App，没有打开新页的权限，这种设定，按照我们常规的思考，对开发者的影响应该不大，毕竟大多数时候，我们并不需要在后台弹出一个页面。

这不是撞上了国内较重的启动页设计，才会出现问题。

针对必要的显示，Google 也明确给出了解决建议，可以判断应用在后台时，通过向用户发送一条通知（Notification），来由用户决定是否开启这个页面。

![](https://mmbiz.qpic.cn/mmbiz_png/liaczD18OicSwIgGwqImEF6tKibiclPDdFDicGGibOVtQG7S80jicPvMbt0vn6JsDE4hic8ID1V7aLokMRdlwU2uibfxCYA/640?wx_fmt=png)

这种解决方案，在本文这个语境中，自然是没有什么鸟用的，走都走了，总不能抱住用户的大腿。

![](https://mmbiz.qpic.cn/mmbiz_png/liaczD18OicSwIgGwqImEF6tKibiclPDdFDicRtRrUbomktWEXYFSpF6RMCdSNJ6yvjRckwDF6LO5M93Car10ec4lVg/640?wx_fmt=png)

这种安全级的升级优化，我觉得按照官方的规范，适配就好了。

四. 适配思路
-------

### 4.1 遵循 MD 规范

前面也提到，如果我们遵循 Material Design 的规范，只让启动图，作为一个对冷启动的优化，瞬时展示，之后立即显示主页，就不会有问题。

在这个过程中，全程只有一个 Activity 参与，自然无需启动一个新页面，也就不会有问题。唯一需要注意的是，在 `setContentView()` 方法之前，别忘了修改当前页面的 Theme。

对于现有项目，这种优化，其实我们大部分的工作，来自如何协调已经在启动页中的各种资源的初始化逻辑，等于之前有一个空转的时间被利用起来初始化资源了，现在这些已经占用的时间，没有了。

不过也别担心，其实有不少优秀的开源库就在解决这些问题，例如之前推文中介绍的 Alibaba 的 Alpha 库，就是一个基于 PERT 图构建的 Android 异步启动框架。

### 4.2 先判断是否前台再跳转

正如小标题上写的，我们可以在启动页跳转到主页时，检测当前页面是否在前台，如果不在，就放弃跳转。因为在后台时，并没有打开新页的动作，自然也不会有警告提示。

这算是一种，在现有项目基础之上，改动最小适配方案。

此时再细化一些，在我们放弃跳转后，可以有两个选择：

_1._ **关闭启动页，下次再被点击重走启动页逻辑**

这很好理解，把启动页 `finish()` 掉，假装它从来没有启动过。下次用户再启动时，之前所有的步骤再走一遍，该显示的广告再多一次曝光。

现在有一些 App 已经是这种方案在优化。

_2._ **关闭启动页，并设置标记位**

在发现启动页不在前台显示时，不做跳转的动作，同时设置一个标志位，但是此时不关闭当前页面。下次启动页再被启动时，直接跳转到主页。

如果选择此方案，我推荐第二种细化的方案。

### 4.3 Activity + Fragment 的方案

此禁止的主要就是开启新的 Activity，但是在同一个 Activity 中，使用不同的 Fragment 来承载不同的业务功能，其实是可以的。

等于是把之前的 SplashActivity，变成 SplashFragment，在主页上先添加 SplashFragment 来完成初始化或者广告的显示，在显示完成之后，移除此 SplashFragment 就好。

这种方案其实是把旧的代码结构调整了，具体逻辑变动并不大，唯一需要注意的依然是 Theme 的切换。

五. 小结时刻
-------

每一次新系统的发布，或多或少都伴随着开发者的一波适配，大多数时候，官方也会给出明确的适配方案，来帮助开发者更快适配新系统。

不过启动页面限制这一项，应该不在 Android 适配规范的计划内，国内开发者还是做好提前准备。如果平时在项目迭代的时候就注意了很多代码的规范，这些改动就相对平滑一些。

你有什么更好的方案，欢迎在留言区讨论。

Reference:

https://shoewann0402.github.io/2019/03/16/android-q-beta-background-activity-starts/

https://developer.android.google.cn/preview/privacy/background-activity-starts

本文对你有帮助吗？**留言、转发、点好看**是最大的支持，谢谢！

「[](http://mp.weixin.qq.com/s?__biz=MzIxNjc0ODExMA==&mid=2247485471&idx=1&sn=c8ef4f7fcf406f1fdb31a78dce6b8d12&chksm=9785113ea0f29828b83c8e54878c2ab91423122e37c4e2406c7b8cd080e4bfe26bacc2afe917&scene=21#wechat_redirect)联机圆桌」👈推荐我的知识星球，一年 50 个优质问题，上桌联机学习。

> 公众号后台回复成长『**成长**』，将会得到我准备的学习资料，也能回复『**加群**』，一起学习进步；你还能回复『**提问**』，向我发起提问。

[![](https://mmbiz.qpic.cn/mmbiz_png/liaczD18OicSwIgGwqImEF6tKibiclPDdFDiced2NunN3r6R8xcicz61cxBdCgLZmj1ibx0fHRlkLNl5yvsuIxFXmtlWQ/640?wx_fmt=png)](http://mp.weixin.qq.com/s?__biz=MzIxNjc0ODExMA==&mid=2247486341&idx=1&sn=2f412b301fcd509cda17a6233b3adf1b&chksm=978512a4a0f29bb27033b22e01bff1beec77ddb0a736224c0fb0bd7f186d1e75c83a1b046837&scene=21#wechat_redirect)

[![](https://mmbiz.qpic.cn/mmbiz_png/liaczD18OicSwJeXpDXYVhv4zEweIavic59qml1oUvES3OlkicqV2GvsCVHaKPaOTs66zTA5zbCdxJvlibxeA2foCWw/640?wx_fmt=png)](http://mp.weixin.qq.com/s?__biz=MzIxNjc0ODExMA==&mid=2247486331&idx=1&sn=27c86b9036be6f0e876ff8e36fc4f07c&chksm=9785125aa0f29b4cc1134a873630095367c6f7d49841a3ce6619499c39d5615201a1be46f406&scene=21#wechat_redirect)

[![](https://mmbiz.qpic.cn/mmbiz_png/liaczD18OicSz0MEm9Q60DrPicYZRPrBSwIXxpzicV1N7mR1QTKx6QaMT9z7L1wjTibiaIibJxQrt1LibH98UlwYicjlMrA/640?wx_fmt=png)](http://mp.weixin.qq.com/s?__biz=MzIxNjc0ODExMA==&mid=2247486308&idx=1&sn=70013952507f6553e3c1c636f2c5da89&chksm=97851245a0f29b531080b12157e1e780ea738bd93fbbc9bc7bba9b628d4d52c8b2a2431d1d86&scene=21#wechat_redirect)

![](https://mmbiz.qpic.cn/mmbiz_jpg/liaczD18OicSxoMtD3tE09ETuiaoibCQklKMnFFYl0ZsC9Ba5PDgXXYV9PdiahKaaBl5f2cDibFO9MZPrAsQdv4QDib8Q/640?wx_fmt=jpeg)