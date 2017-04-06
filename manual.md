# 说明文档(v1.3)


## 命名规范
- 类名和文件名相同
- 区分大小写
- 一个类一个文件
- 文件扩展名统一为.hpp
- 所有类在sjtu命名空间下

## 思路

用户首先通过`User::login`登陆 ，确认自身身份为`User`或`Admin`，调用其方法进行操作
用户的大部分操作会通过访问`RailwayMinistry`来实现，而`RailwayMinistry`的内部为容器存储的`Train`和`User`
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
|iFileManager.hpp|输入文件管理|
|oFileManager.hpp|输出文件管理|
|~~Log.hpp~~|~~日志~~|
|LogManager.hpp|日志管理|
|Exceptions.hpp|异常处理|
|~~LoginManager.hpp~~|~~登陆管理~~|
|Ticket.hpp|车票类|
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
|int|operator-(Date a,Date b)|返回两个时间相差的分钟数|
|Date|operator+(Date a,int b)|返回a往后b分钟的时刻|
|string|toString(Date a)|显示日期，精确到分钟|
|void|read(iFileManager&)|读取自身信息|


### iFileManager类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|void|openFile(string id)|打开文件|
|void|saveFile()|保存文件|
|void|closeFile()|关闭文件|
|iFileManager&|operator>>(T x)|读入T|
### oFileManager类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|void|openFile(string id)|打开文件|
|void|saveFile()|保存文件|
|void|closeFile()|关闭文件|
|oFileManager&|operator<<(T x)|输出T|

### Exceptions类
|类名称|描述|
|:------:|:-----:|
|invalidInput|输入不合法|
|invalidStaion|不合法的车站|
|invalidTrain|不合法的车次|

### ~~LoginManager类~~

### Ticket类
注意`Ticket.hpp`中有一个枚举类型叫做`TicketLevel`

|返回值|方法|描述|
|:------:|:-----:|:-----:|
|double|cost()|返回票价|
|double|train()|返回车次|
|Station|start()|返回起点|
|Station|target()|返回终点|
|TicketLevel|level()|返回车票种类|
|Date|startDate()|返回起点时间|
|Date|targetDate()|返回终点时间|
|void|read(iFileManager&)|读取自身信息|

### User类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|vector< Train >|queryTrainByST(Station start,Station target)|通过起点终点查询车次信息|
|vector< Train >|queryTrainByStart(Station station)|通过起点查询车次信息|
|vector< Train >|queryTrainByTarget(Station station)|通过终点查询车次信息|
|vector< Train >|queryTrainByStaion(Station station)|通过途径车站查询车次信息|
|vector< Train >|queryTrainByDate(Date date)|通过出发日期查询车次信息|
|vector< Train >|queryTrainByID(str   ing id)|通过车次编号查询车次信息|
|vector< Ticket >|queryTicket()|查询自身购票|
|string|queryInfo()|查询自身信息|
|bool|buyTicket(string,Station start,Station target,TicketLevel,int num)|买票|
|bool|refundTicket(string,Station start,Station target,TicketLevel,int num)|退票|
|bool|updateInfo(string pwd,string name)|更新信息|
|void|read(iFileManager&)|读取自身信息|
|pair< string , bool >|reg(string id,string pwd,string name)|注册一个用户名为id，密码pwd，昵称为name的用户|
|pair< string , bool >|login(string id,string pwd)|登陆，返回错误信息和是否成功|
|pair< string , bool >|updateInfo(string id,string pwd,string name)|将用户名为id的密码修改为pwd，昵称修改为name|
|bool|isAdmin()|判断是否为管理员|

### Admin类
需要注意`Admin`类继承自`User`类

|返回值|方法|描述|
|:------:|:-----:|:-----:|
|void|addTrain(Train train)|增加车次|
|void|updateTrain(Train train)|修改车次|
|void|removeTrain(string id)|删除车次|
|void|startSale(Train train)|开始卖票|
|void|endSale(Train train)|停止卖票|
|Log|readUser(string id)|查看用户信息|
|Log|readLog()|查看系统日志|

### Station类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|string|getName()|返回车站名称|
|string|getCity()|返回所在城市名称|
|void|read(iFileManager&)|读取自身信息|

### Train类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|Station|getStart()|返回首发车站|
|Station|getTarget()|返回终点车站|
|vector< Station >|getWay()|返回路线|
|double|getCost(Station a,Station b,TicketLevel)|返回车票价格|
|Date|getTime(Staion)|返回到达时刻|
|int|getRestTicket(Station a,Station b,TicketLevel)|返回剩余车票数量|
|void|buyTicket(Station a,Station b,TicketLevel,int num)|买票|
|void|refundTicket(Station a,Station b,TicketLevel,int num)|退票|
|void|startSale(Train train)|开始卖票|
|void|endSale(Train train)|停止卖票|
|bool|canSell()|是否可以买票|
|void|read(iFileManager&)|读取自身信息|

### RailwayMinistry类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|vector< Train >|getTrainByStart(Station station)|返回首发station的车次|
|vector< Train >|getTrainByTarget(Station station)|返回结束station的车次|
|vector< Train >|getTrainByStation(Station station)|返回经过station的车次|
|vector< Train >|getTrainByDate(Date date)|通过时间查询车次|
|Train|getTrainByID(string id)|通过id访问车次|
|void|addTrain(Train train)|增加车次|
|void|updateTrain(Train train)|修改车次|
|void|removeTrain(string id)|删除车次|
|void|startSale(Train train)|开始卖票|
|void|endSale(Train train)|停止卖票|
|vector< Ticket >|queryTicket(string id)|id用户查询自身购票|
|string|queryInfo(string id)|id用户查询自身信息|
|vector< Ticket >|buyTicket(string id,Train train,Station start,Station target,TicketLevel,int num)|id用户买票|
|bool|refundTicket(string id,Train train,Station start,Station target,TicketLevel,int num)|id用户退票|
|bool|updateInfo(string id,string pwd,string name)|id用户更新信息|
|void|read(iFileManager&)|读取自身信息|
|Log|readUser(string id)|查看用户信息|
|bool|isAdmin(string id)|判断是否为管理员|
|vector< string >|readLog()|查看系统日志|

