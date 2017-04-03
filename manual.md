# 说明文档(v1.0)


## 命名规范
- 类名和文件名相同
- 区分大小写
- 一个类一个文件
- 文件扩展名统一为.hpp
- 所有类在sjtu命名空间下

## 思路

用户首先通过`LoginManager`登陆 ，确认自身身份为`User`或`Admin`，调用其方法进行操作
用户的大部分操作会通过访问`RailwayMinistry`来实现，而`RailwayMinistry`的内部为容器存储的`Train`
`FileManager`类负责从文件读写数据，`Exceptions`负责异常处理

## 文件

|      文件名     | 描述   |
|:-----------------:|:-----------------:|
|lib/algo.hpp|常用算法|
|lib/vector.hpp|vector容器|
|lib/map.hpp|map容器|
|lib/set.hpp|set容器|
|lib/shared_ptr.hpp|智能指针|
|lib/utility.hpp|pair类|
|lib/Date.hpp|日期类|
|File.hpp|文件|
|FileManager.hpp|文件管理|
|Exceptions.hpp|异常处理|
|LoginManager.hpp|登陆管理|
|User.hpp|普通用户|
|Admin.hpp|管理员用户|
|Station.hpp|车站|
|Train.hpp|车次|
|RailwayMinistry.hpp|铁道部|

## 类接口说明

### vector,set,map
人肉实现，和STL用法基本相同

### Date类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|int|opertor-(Date a,Date b)|返回两个时间相差的分钟数|
|string|toString(Date a)|显示日期，精确到分钟|

### FileManager类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|int|readInt(File f)|从文件中读入一个整数|


### Exceptions类
|类名称|描述|
|:------:|:-----:|
|invalidInput|输入不合法|

### LoginManager类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|bool|reg(string id,string pwd,string name)|注册一个用户名为id，密码pwd，昵称为name的用户|
|pair< string , bool >|login(string id,string pwd)|登陆，返回错误信息和是否成功|

### User类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|vector< Train >|queryTrainByStart(Station station)|通过起点查询车次信息|

### Admin类
需要注意`Admin`类继承自`User`类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|void|addTrain(Train train)|增加车次|

### Station类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|string|getName()|返回车站名称|

### Train类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|Station|getStart()|返回首发车站|



### RailwayMinistry类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|vector< Train >|getTrainByStation(Station station)|返回经过station的车次|