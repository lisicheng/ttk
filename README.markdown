<!--
	本文档为Markdown格式，可以使用以下命令生成HTML格式文档。
	markdown README.markdown > README.html

	参见： http://daringfireball.net/projects/markdown/syntax
-->

# Troodon ToolKit
代码地址：`git://github.com/yuanyelele/ttk.git`

## 目录结构
* `config.mk`: 适用于S60第三版的配置文件
* `config_2nd.mk`: 适用于S60第二版的配置文件
* `.gitignore`: git忽略的文件列表
* `group`: S60项目定义文件
* `inc`: 头文件	
	* `framework`: S60 GUI框架类
	* `symttk`: Symbian平台相关TTK类
	* `ttk`: 平台无关TTK类
		* `common`: 平台无关通用类，如颜色、矩形等
	* `ui`: TTK控件样例
* `Makefile`: 适用于S60第三版的Makefile
* `Makefile_2nd`: 适用S60第二版的Makefile
* `README.markdown`: Markdown格式的说明文件
* `rss`: S60资源文件
* `sis`: S60打包配置
* `src`: 源文件，子目录结构同`inc`
* `ttk.doxygen`: Doxygen配置，用于自动生成API文档


## 代码规范
除了以下的若干条，一律采用[Google C++ 代码风格](http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml)。

### 注释
注释一律采用`/*...*/`风格，不使用`//...`风格。必要时使用Doxygen风格（`/**..*/`）注释函数参数等，以便于生成文档。

### 缩进
无论是平台相关，还是平台无关的代码，缩进一律采取[Stroustrup风格](http://www2.research.att.com/~bs/bs_faq2.html#layout-style)。用长度等于8个空格的Tab键缩进，但是不要用空格替换Tab。

### 全局标示符
所有平台无关的TTK全局标示符（如类名、枚举名等）均以`Ttk`开头，全局常量以`kTtk`开头。

### 文件名
文件名中不要包含类前缀`Ttk`。

### Symbian平台相关代码
Symbian平台相关代码遵循[Symbian代码规范](http://www.forum.nokia.com/info/sw.nokia.com/id/70984bb2-4880-4dcc-a078-21f24224c5fb/Symbian_OS_Coding_Conventions_v1_0_en.pdf.html)，除了以下几点：

* 在类型标识字母（`C/T/R/M`）后，类名以`SymTtk`开头，如`CSymTtkGc`。

* 当Symbian相关类继承了TTK接口时，继承函数的声明和定义头均使用接口中的风格。

* 文件名为去除了类型标识字母和`SymTtk`的类名，但改为小写。例如文件`gc.h`的内容为：

		#ifndef SYMTTK_GC_H
		#define SYMTTK_GC_H
		class CSymTtkGc {
		};
		#endif /* SYMTTK_GC_H */

