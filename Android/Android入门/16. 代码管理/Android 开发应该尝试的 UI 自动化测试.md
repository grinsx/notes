> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 https://juejin.im/post/5b66de2c6fb9a04fbd1b4725

> 本文由[`玉刚说写作平台`](https://link.juejin.im?target=http%3A%2F%2Frenyugang.io%2Fpost%2F75)提供写作赞助
> 
> 原作者：`却把青梅嗅`
> 
> 版权声明：本文版权归微信公众号`玉刚说`所有，未经许可，不得以任何形式转载

## 困境

接下来我将说到这种情况并非个例——作为一个 Android 开发者，当我实现了一个界面的一些功能，或者对界面上某些功能进行了修改，我该如何去查收我想要的结果呢？

最简单的方式就是**直接编译运行** App，通过自己的操作对界面进行交互，从个人的视觉效果上进行功能的检查，比如我实现了一个 RecyclerView，我就打开界面，看看这个列表是否正确显示在了界面上。

不久之后，我觉得某些地方代码不是很好，于是我改了一些代码，我怕会出现问题，于是为了保证项目能够不出问题（至少是避免低级的错误），我选择**再次编译运行**，验收结果。

再深入一点，如果每个版本发布前都需要这么多次测试，或者每当我们简单修改了一下代码，就需要**更多次重复**进行以上步骤，并检测结果，来来往往，反反复复，实在令人乏味。

![](https://user-gold-cdn.xitu.io/2018/8/5/16509d3bb3a1ad39?imageView2/0/w/1280/h/960/format/webp/ignore-error/1)

也许， UI 自动化测试是一劳永逸解决这个问题的方案之一。

## UI 自动化测试简介

**充满热情，一腔热血，说学就学，我行我上。**

相信我，不要这样，这和学习**库**或者**框架**不一样，UI 自动化测试是一个**专业技能**。不信的话，请参考一下各大机构对于**测试工程师**的培训周期，系统性走一遍全日制要几个月，闲暇时间学习？学不完的，而且，没必要。

以 [Android 官方文档](https://link.juejin.im?target=https%3A%2F%2Fdeveloper.android.com%2Ftraining%2Ftesting%2Ffundamentals)的概述，AndroidStudio 提供了几种 UI 测试工具供开发者使用。

> 事实上 UI 的自动化测试工具很多，但对于 Android 开发者来讲，掌握其中的 1 至 2 项，就足以在 UI 测试领域立足，本文仅简单介绍基础的几款工具以抛砖引玉。

### 1\. Monkey

**Monkey** 是 Android SDK 自带的测试工具，在测试过程中会向系统发送伪随机的用户事件流，如按键输入、触摸屏输入、手势输入等)，实现对正在开发的应用程序进行压力测试，也有日志输出。实际上该工具只能做程序做一些压力测试，由于测试事件和数据都是随机的，不能自定义，所以有很大的局限性。

### 2\. Instrumentation

**Instrumentation** 是早期 Google 提供的 Android 自动化测试工具类，虽然在那时候 JUnit 也可以对 Android 进行测试，但是 Instrumentation 允许你对应用程序做更为复杂的测试，甚至是框架层面的。通过 Instrumentation 你可以模拟按键按下、抬起、屏幕点击、滚动等事件。Instrumentation 是通过将主程序和测试程序运行在同一个进程来实现这些功能，你可以把 Instrumentation 看成一个类似 Activity 或者 Service 并且不带界面的组件，在程序运行期间监控你的主程序。缺点是对测试人员来说编写代码能力要求较高，需要对 Android 相关知识有一定了解，还需要配置 AndroidManifest.xml 文件，不能跨多个 App。

### 3\. UiAutomator

**UiAutomator** 也是 Android 提供的自动化测试框架，基本上支持所有的 Android 事件操作，对比 Instrumentation 它不需要测试人员了解代码实现细节（可以用 UiAutomatorviewer 抓去 App 页面上的控件属性而不看源码）。基于 Java，测试代码结构简单、编写容易、学习成本，一次编译，所有设备或模拟器都能运行测试，能跨 App（比如：很多 App 有选择相册、打开相机拍照，这就是跨 App 测试）。缺点是只支持 SDK 16（Android 4.1）及以上，不支持 Hybird App、WebApp。

### 4\. Espresso

**Espresso** 是 Google 的开源自动化测试框架。相对于 Robotium 和 UIAutomator，它的特点是规模更小、更简洁，API 更加精确，编写测试代码简单，容易快速上手。因为是基于 Instrumentation 的，所以不能跨 App。

> 以上这些工具的概述，节选引用自[知乎：Android 手机自动化测试工具有哪几种？](https://link.juejin.im?target=https%3A%2F%2Fwww.zhihu.com%2Fquestion%2F19716849)

### 如何入门？

UI 的自动化测试的是一个复杂的系统，所谓**望山跑死马**，作为 Android 开发者，我们想要通过闲暇的时间，期望**短期能够精通 UI 自动化测试是不现实的**，但是每次都运行 app 手动测试又显得很蠢，最好的方式，是通过了解并学习一个经典的 UI 测试工具，在了解到 UI 自动化测试的好处之后，再选择**继续深入**还是**功成身退**。

有心的同学已经注意到了，上文中最后介绍的那个 **Espresso** 怎么这么眼熟呢？确实如此，在 AndroidStudio2.2 版本之后，在新建的项目中，AndroidStudio 会默认添加 Espresso 的依赖。

这样看来，**Espresso** 显然是一个不错的选择。正如 Google 所希望的，当 Android 的开发者利用 Espresso 写完测试用例后，能一边看着测试用例自动执行，一边享受一杯香醇的 Espresso(意式咖啡)。

## Espresso 学习指南

### 没事走两步

Google 官方希望我们通过 Espresso 减少重复的劳动，那么这所谓的 **UI 自动化测试**效果如何呢，正所谓**手下见真章**，我们来看一下 Google 的 todo App 的测试代码运行时的效果：

![](https://user-gold-cdn.xitu.io/2018/8/5/16509d3bb4d4c6ef?imageView2/0/w/1280/h/960/format/webp/ignore-error/1)

Espresso 的原理是，通过测试代码模拟用户对 UI 元素的操作，之后再校验（verify）操作后的结果，和我们**人为操作**不同，Espresso 能够在短时间内测试所有的 case，正如你所见的一样。

我们不禁这样想，如果一个界面涉及到很多的操作，没有 Espresso 测试代码之前，每次修改，工作的责任感需要让我自己先跑一遍所有功能，然后才敢打包扔给 QA，但是如果我写好了自动化测试代码，是不是意味着每次改完代码，只需跑一遍测试代码就代替了之前的手工操作呢？

![](https://user-gold-cdn.xitu.io/2018/8/5/16509d3c38485a45?imageView2/0/w/1280/h/960/format/webp/ignore-error/1)

如您所见，本次测试了一个界面 19 个不同的操作，整个自动化过程共花费了 4m34s，**但在这个过程中我可以冲一杯咖啡，或者看看技术博客，甚至是发呆——我惬意地得到了期冀的结果**。

如果我负责的功能模块所有界面，都覆盖了这样的测试代码，多好啊......——如果屏幕面前的您，有学习借助自动化测试工具**偷懒**的想法，**请坚持阅读下去**，以一个**开发人员**而非专业测试人员的视角，分享**学习自动化测试的经验**，这也正是本文的目的。

### 主旨

本文的目标是，以自己的学习经历为基础，为想要学习 Espresso（或者有这个想法）的同学，提供一个**系统性的规划和建议**。

这意味着，本文不会去详细阐述**每个 API 的使用**，于我而言，这些应该交给**官方文档**去阐释，当然，对于 API 而言，我也不认为能够讲述的比官方文档更优秀。

我会通过一些简单的测试代码阐述 UI 自动化测试所需要的一些**基础或思想**，但是**代码本身不应该是本文的重点**，我更希望，当您读完本文，您能有**啊，原来 Espresso 的 UI 测试应该这么学**之感——而不是**哦，原来这个 API 是这么用的**。

如果将本文的定义类比于**该知识体系**的**目录**或者**导航**，我觉得再恰当不过。

### 如何学习 Espresso

我的建议是按照以下步骤进行学习：

**1\. Fork Google 官方的 Demo 代码，运行并感受测试代码的威力**

Google 官方的 todo 案例地址：

https://github.com/googlesamples/android-architecture

我们拉下来代码后，选一个您比较感兴趣的分支，比如比较简单一点的 todo-mvp 分支，这个分支中代码的实现仅仅使用了 MVP 的架构，学习起来并不复杂。

我们来看一下项目的目录结构：

![](https://user-gold-cdn.xitu.io/2018/8/5/16509d3d25c24e6c?imageView2/0/w/1280/h/960/format/webp/ignore-error/1)

其中 androidTest 和 androidTestMock 都是 UI 测试的代码，我们先右键点击 androidTest 文件夹，run 该文件夹下的所有 UI 测试 case。

![](https://user-gold-cdn.xitu.io/2018/8/5/16509d3d7d38e97d?imageView2/0/w/1280/h/960/format/webp/ignore-error/1)

选中设备后，AndroidStudio 就会编译并自动打包（注意实际上此处的测试打包和实际生产的打包并不一样），然后自动在设备上运行所有的测试 case——就和上文中的效果一样。

看到这里，我们不仅感叹测试代码的强大，不要沉迷于此，我们继续第二步：

**2\. 阅读 Espresso 的官方文档**

如果点进去看测试代码的话，我们会比较懵逼，因为我们对于 Espresso 的使用一无所知，那么接下来我们要去做的，就是阅读 Espresso 的官方文档了：

[Espresso 官方文档:](https://link.juejin.im?target=https%3A%2F%2Fdeveloper.android.com%2Ftraining%2Ftesting%2Fespresso%2Fbasics)

> https://developer.android.com/training/testing/espresso/basics

[Espresso 官方文档中文翻译:](https://link.juejin.im?target=https%3A%2F%2Flovexiaov.gitbooks.io%2Fofficial-espresso-doc%2Fcontent%2F)

> https://lovexiaov.gitbooks.io/official-espresso-doc/content/

中文翻译的 gitbook 的确不好找，在此不仅感叹 UI 自动化测试的小众性，特别感谢译者 [lovexiaov](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2Flovexiaov)，没有你的分享精神，我就只能考虑自己去硬啃英文文档了。

> 实话说，中文的文档部分翻译不够准确，建议大家，有能力还是看英文原版，我更建议大家中英文对照学习。

这一步，我们不需要深入学习并使用文档中列举的所有 API，只需要参照文档看得懂 todoApp 中测试代码的用意就行了。

**3\. 付诸实践**

当我们参照 API 文档，并且能够基本看得懂 demo 代码中，大部分测试 case 想要干什么，我们接下来就可以尝试付诸实践了。

## 实践

接下来我将会用简单的代码阐述 Espresso 的简单使用。

### 1.Hello Espresso!

来一个最简单的 demo，当我们点击一个 Button，让界面某个 TextView 显示 **HelloEspresso** 的文字内容。

我们忽略 xml 布局的实现，简单看一下 Activity 中的部分 Java 代码：

```
public void onViewClicked(View view) {
      switch (view.getId()) {
          case R.id.button:
              // 点击button后，textview显示hello espresso!
              textView.setVisibility(View.VISIBLE);
              textView.setText("hello espresso!");
              break;
      }
}
复制代码
```

非常简单，测试代码自然也浅显易懂：

```
@RunWith(AndroidJUnit4.class)
public class MainActivityTest {

    @Rule
    public ActivityTestRule<MainActivity> rule =
            new ActivityTestRule<>(MainActivity.class);

    @Test
    public void clickTest() {
        //检验：一开始，textView不显示
        onView(withId(R.id.textView))
                .check(matches(not(isDisplayed())));

        //检验：button的文字内容
        onView(withId(R.id.button))
                .check(matches(withText("修改内容")))
                .perform(click());  //操作：点击按钮

        //检验：textView内容是否修改，并且变为可见
        onView(withId(R.id.textView))
                .check(matches(withText("hello espresso!")))
                .check(matches(isDisplayed()));
    }
}
复制代码
```

代码非常简单，逻辑也很清晰，我们测试的思路是，找到我们要操作的界面元素，然后操作该界面元素，然后校验 UI 的变化。

在这个测试中，当我们点击了 button 后，会校验：界面上 TextView 变为可见，同时附有 “hello espresso!” 的内容——如果测试失败了，说明我们预期的操作并未得到预期的结果，我们就需要去检查代码了。

### 2\. 模拟用户的登陆操作

接下来我们跳转另外一个场景，稍微复杂一点，界面上有一个 EditText，负责**用户输入账号**，还有一个 Button，负责**登录**，还有一个 TextView，当用户点击 Button 后，TextView 会显示**登录成功**并且**清空输入框**：

```
public void onViewClicked(View view) {
      switch (view.getId()) {
          case R.id.button2:
            // 登陆成功并且清空输入框
            textView.setVisibility(View.VISIBLE);
            textView.setText("登录成功");
            editText.setText("");
            break;
      }
}
复制代码
```

我们可以这样补充测试 Case：

```
@Test
    public void loginTest() throws Exception {
        //先清除editText的内容，然后输入，然后关闭软键盘，最后校验内容
        //这里如果要输入中文，使用replaceText()方法代替typeText()
        onView(withId(R.id.editText))
                .perform(
                    clearText(),
                    replaceText("username"),
                    closeSoftKeyboard()
                )
                .check(matches(withText("username")));

        // 操作：点击Button
        onView(withId(R.id.button2))
                .perform(click());

        //校验：textView的内容和可见
        onView(withId(R.id.textView))
                .check(matches(withText("登录成功")))
                .check(matches(isDisplayed()));

        //校验：editText的文字内容（被清空）和hint
        onView(withId(R.id.editText))
                .check(matches(withText("")))
                .check(matches(withHint("请输入账户名")));
    }
复制代码
```

大功告成——和基本案例基本差不多，都是通过简单的对 View 的**操作** + **校验**完成了 UI 的测试代码编写。

看起来我们已经**熟悉了 Espresso 的使用套路**，我已经有信心在真实的项目中应用它了。

### 3\. 熟练使用 Espresso 进行 UI 自动化测试

正所谓**行百里路半九十**，当我们将看起来并不复杂的 Espresso 应用在真实的项目中时，我们马上就会遇到一个很严重的问题，那就是：

**并非所有的 UI 操作都是同步响应的！**

Espresso 进行一个简单的同步功能测试并不难，比如我们点击了一个 Button, 点击后改变对应某个 TextView 的内容，这很简单。但实际正常开发中，这种简单的逻辑测试是很少见的，相反，我们需要测试的是各种各样的异步测试，比如：

> 情景一：点击进入 Activity，网络请求数据加载，成功后数据展示在界面上。 情景二：点击进入 Activity，获得缓存，网络请求数据加载，成功后数据展示在界面上，处理缓存。 情景 N : ......

假设这样一个简单的网络请求测试：

```
@Test
public void testHttp() {
   // 我们请求网络数据，成功后让TextView显示"网络请求成功"
   // 同时ImageView从不可见变为可见

    //如果我们直接检查是不是请求到了数据
    onView(withId(R.id.textView)).check(matches(withText("网络请求成功！")));
    onView(withText(R.id.imageView)).check(matches(isDisplayed()));
}
复制代码
```

如果我们直接测试，那么很大概率会报错，因为**在我们要测试数据是否展示在 UI 上时，网络数据很有可能还没有获取到。**

这很难处理，因为我们不知道数据到底什么时候才能获取到，有同学抖了个机灵，说我们可以这样：

```
 @Test
public void testHttp() {
    // 我们一进来就先让他等待5秒，等数据加载完毕再检查UI
    Thread.sleep(5000)；

    // 5秒结束，我们检查是不是请求到了数据
    onView(withId(R.id.textView)).check(matches(withText("网络请求成功！")));
    onView(withText(R.id.imageView)).check(matches(isDisplayed()));
}
复制代码
```

这样可以实现吗，这个**大概率真的可以**，但是这种测试显然问题很多，因为网络情况是在不断变化的，也许 0.5s 就能获取网络数据，也有可能数十秒后才能获取，这样前者导致我们浪费了 4.5s 的时间，后者在网络状态属于正常的时候测试结果失败，这都是我们不愿看到的结果。

我们更希望在获取到网络数据之后，立即进行下一步的测试，因此我们需要对网络数据的获取情况进行监听。

但是问题来了，**如何在 UI 测试代码中，对真实的网络状态进行监听呢？**

这个问题难倒了我，好在 Google 的工程师们已经在 todo 的 demo 中提供了一种解决的方式，我们来看一看官方的方案。

### 4\. 异步操作的测试思路

Google 官方提供了 **IdlingResource** 以供开发者进行 UI 的异步测试，对于 **IdlingResource** 的解释说明，我们可以参照官方文档：

https://developer.android.com/training/testing/espresso/idling-resource

或者中文文档对于 IdlingResource 的解释：

https://lovexiaov.gitbooks.io/official-espresso-doc/content/chapter6.html

我不会用大段代码阐述如何使用，它的基本原理是：在**生产代码中**，定义一个 Flag（标记），当开始异步请求前，修改 Flag 的状态，当网络请求结束后，将 Flag 的状态**重置**，这时候 Flag 状态修改的事件会被发送**通知**给注册的对象（比如测试代码）：

```
@Before
public void setUp() throws Exception {
    idlingresource = activityRule.getActivity().getIdlingresource();
}

@Test
public void onLoadingFinished() throws Exception {
    //  不再需要这样的代码
    //  Thread.sleep(5000);

    // 注册异步监听，此时测试会被挂起
    // 当网络请求结束后，生产代码中Flag状态的改变，会继续执行测试代码
    Espresso.registerIdlingResources(idlingresource);

    // 继续执行代码
    onView(withId(R.id.text))
            .check(matches(withText("success!")));
}

@After
public void release() throws Exception {
    // 当然，我们需要在测试结束后取消注册，释放资源
    Espresso.unregisterIdlingResources(idlingresource);
}
复制代码
```

这种行为的好处不言而喻，它能够在异步结束之后马上执行接下来的测试代码，从效果上来说，相比`Thread.sleep(5000);`不知好了多少。

它的缺点也很明显，那就是测试代码实际**需要依赖对生产代码进行配置**（本文中并未展示，请参考 todoDemo 或者[这篇文章](https://link.juejin.im?target=https%3A%2F%2Fblog.csdn.net%2Fmq2553299%2Farticle%2Fdetails%2F74490718)）。

难道就没有更好的解决方案吗？当然有，Google 对此的建议是，重构项目代码（比如增加 product flavors，或者通过依赖注入等等），使其变得可测试性——到这一步，请慎重考虑，因为这已经涉及到项目的架构以及项目管理的层级上了。

### 5\. 更多

实际上，Espresso 在应用在实际项目中，需要我们去面对的问题并不少，绝大多数情况下，这些问题都能够通过**搜索引擎**然后**亲自实践**去解决—— 你绝不是一个人在战斗。

## 小结——坚持还是放弃？

很多同学都了解**单元测试**和 **UI 自动化测试**的重要性，但是这些工具需要**不菲的时间成本**，那么它们真的还有必要去学习吗？

有位同学举手了，他同样表示——有时虽然修改一个小功能，需要开发者多次手动测试很麻烦，但是也**并非不可接受**，至少上班时，在项目编译运行期间，我可以**切换网页，看看新闻摸摸鱼**。

![](https://user-gold-cdn.xitu.io/2018/8/5/16509d3d87ceec13?imageslim)

当然还有这样的情况，作为一个开发人员，即使我学会了自动化测试，我也不一定有机会去应用它，**直接尝试应用在一个已经完善的成熟项目中，是不现实的**；这样的话，会不会出现，学会了但根本用不到的窘境？

每个人都不能保证将来还是否还会遇到曾经的问题，如果遇到了，我该怎么做，是选择**继续躲避**，还是**一劳永逸**；而且，即使学会了，如何保证这能成为我**核心竞争力的一部分**，而不是学会了却用不到，最终被慢慢忘记？

的确，我们有时的确**没有必要**为工作做出**额外的付出（思考和实践）**，万一搞砸了，反而不如不做。但是我要阐述的一点是：**不做并不意味着问题被解决了——你只是暂时避开了它**，而下一次遇到它的时候，你仍需去面对这个困境；并且，如果将测试任务交给了代码，摸鱼的时候岂不更加轻松？正所谓，**授人以渔，劳神费力。** 而——

![](https://user-gold-cdn.xitu.io/2018/8/5/16509d3db2ce70b3?imageView2/0/w/1280/h/960/format/webp/ignore-error/1)

### 我的思路

言归正传，对于**如何实践自动化测试**，我的方式是对个人的一些工具代码进行 **UI 自动化测试的覆盖**，在进一步完善自己的工具同时，深入了解 Espresso。

笔者对于 Espresso 的经验所得来自于自己的 **[Github](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2Fqingmei2) **的[这个工具](https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2Fqingmei2%2FRxImagePicker)，它是 Android 的一个**响应式图片选择器 **，因此每次发布新版本笔者都需要自己测试 UI，而 **UI 自动化测试**无疑可以减少这些重复的操作。 ——这个库 UI 测试的更详细过程并非本文的重点，我在另一篇文章中去阐述了它:

[全副武装！AndroidUI 自动化测试在 RxImagePicker 中的实践历程](https://link.juejin.im?target=https%3A%2F%2Fwww.jianshu.com%2Fp%2F6b78f6f93430)

**一千个观众眼中有一千个哈姆雷特**，只要感兴趣，总能找到适合自己的方式，本文所讲述的 Espresso 仅仅是 **UI 自动化测试**这门专业技术的**一部分**，但我认为它很契合 Android 开发者，并借助它为自己的 UI 界面进行**白盒测试（也有朋友称 Espresso 为灰盒测试）**，正如官方文档所描述的（下为译文）：

> Espresso 的使用群体为坚信自动化测试是开发周期中必不可少的一部分的开发者。虽然它可被用来做黑盒测试，但 Espresso 会在对**被测代码库熟悉的人**手中**火力全开**。

在我们感叹 AndroidStudio 默认提供的依赖库中，**JUnit4** 可以让我们通过单元测试保证最小模块代码的可靠性，**ConstraintLayout** 让我们减少大量布局嵌套的同时慢慢抛弃了 **RelativeLayout** 的同时，请也不要忽视 **Espresso**，真正了解了它并付诸实践，便会对它强大的 UI 自动化测试功能爱不释手。

![](https://user-gold-cdn.xitu.io/2018/6/6/163d3319859594d4?imageView2/0/w/1280/h/960/format/webp/ignore-error/1)欢迎关注我的微信公众号「玉刚说」，接收第一手技术干货