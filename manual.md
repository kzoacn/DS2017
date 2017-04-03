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
|TicketLevel.hpp|车票等级|
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

### File类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|void|open(string fileName)|打开文件|
|void|close()|关闭文件|

### FileManager类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|void|openFile(File f)|打开文件|
|void|saveFile()|保存文件|
|void|closeFile()|关闭文件|
|int|readInt()|从文件中读入一个整数|
|Date|readDate()|从文件中读入时间|
|Station|readStation()|从文件中读入一个车站|
|vector< Train >|readTrain()|从文件中读入一排车次|
|string|readString()|从文件中读入一个字符串|
|User|readUser()|从文件中读入一个用户信息|
|void|appendInt(Int)|向文件中写入一个整数|
|void|appendDate(Date)|向文件中写入时间|
|void|appendStation(Station)|向文件中写入一个车站|
|void|appendTrain(vector< Train >)|向文件中写入一排车次|
|void|appendString(string)|向文件中写入一个字符串|
|void|appendUser(User)|向文件中读入一个用户信息|


### Exceptions类
|类名称|描述|
|:------:|:-----:|
|invalidInput|输入不合法|
|invalidStaion|不合法的车站|
|invalidTrain|不合法的车次|

### LoginManager类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|pair< string , bool >|reg(string id,string pwd,string name)|注册一个用户名为id，密码pwd，昵称为name的用户|
|pair< string , bool >|login(string id,string pwd)|登陆，返回错误信息和是否成功|
|void|updateInfo(string id,string pwd,string name)|将用户名为id的密码修改为pwd，昵称修改为name|
|bool|isAdmin(string id)|判断是否为管理员|
|User|getUser(string id)|获取用户|
|Admin|getAdmin(string id)|获取管理员|

### User类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|vector< Train >|queryTrainByST(Station start,Station target)|通过起点终点查询车次信息|
|vector< Train >|queryTrainByStart(Station station)|通过起点查询车次信息|
|vector< Train >|queryTrainByTarget(Station station)|通过终点查询车次信息|
|vector< Train >|queryTrainByStaion(Station station)|通过途径车站查询车次信息|
|vector< Train >|queryTrainByDate(Date date)|通过出发日期查询车次信息|
|vector< Train >|queryTrainByID(string id)|通过车次编号查询车次信息|
|vector< string >|queryInfo()|查询自身信息|
|bool|buyTicket(string,Station start,Station target,TicketLevel,int num)|买票|
|bool|refundTicket(string,Station start,Station target,TicketLevel,int num)|退票|
|bool|updateInfo(string pwd,string name)|更新信息|

### Admin类
需要注意`Admin`类继承自`User`类

|返回值|方法|描述|
|:------:|:-----:|:-----:|
|void|addTrain(Train train)|增加车次|
|void|updateTrain(Train train)|修改车次|
|void|removeTrain(string id)|删除车次|
|void|startSale(Train train)|开始卖票|
|void|endSale(Train train)|停止卖票|
|vector< string >|readUser(string id)|查看用户信息|
|string|readLog()|查看系统日志|

### Station类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|string|getName()|返回车站名称|
|string|getCity()|返回所在城市名称|

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

### RailwayMinistry类
|返回值|方法|描述|
|:------:|:-----:|:-----:|
|vector< Train >|getTrainByStart(Station station)|返回首发station的车次|
|vector< Train >|getTrainByTarget(Station station)|返回结束station的车次|
|vector< Train >|getTrainByStation(Station station)|返回经过station的车次|
|vector< Train >|getTrainByDate(Date date)|返回经过station的车次|
|vector< Train >|getTrainByID(string id)|返回经过station的车次|
|void|addTrain(Train train)|增加车次|
|void|updateTrain(Train train)|修改车次|
|void|removeTrain(string id)|删除车次|
|void|startSale(Train train)|开始卖票|
|void|endSale(Train train)|停止卖票|



