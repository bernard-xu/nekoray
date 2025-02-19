#include "includes.h"

#include <QApplication>
#include <QHostInfo>
#include <QUrl>
#include "AbstractBean.hpp"

namespace NekoGui_fmt {
    AbstractBean::AbstractBean(int version) {
        this->version = version;
        _add(new configItem("_v", &this->version, itemType::integer));
        _add(new configItem("name", &name, itemType::string));
        _add(new configItem("addr", &serverAddress, itemType::string));
        _add(new configItem("port", &serverPort, itemType::integer));
        _add(new configItem("c_cfg", &custom_config, itemType::string));
        _add(new configItem("c_out", &custom_outbound, itemType::string));
        _add(new configItem("country", &country, itemType::string));
    }

    void AbstractBean::SetCountryFromDisplay() {
        this->country = DisplayCountry();
    }

    QString AbstractBean::ToNekorayShareLink(const QString &type) {
        auto b = ToJson();
        QUrl url;
        url.setScheme("nekoray");
        url.setHost(type);
        url.setFragment(QJsonObject2QString(b, true)
                            .toUtf8()
                            .toBase64(QByteArray::Base64UrlEncoding));
        return url.toString();
    }

    QString AbstractBean::DisplayAddress() {
        return ::DisplayAddress(serverAddress, serverPort);
    }

    QString AbstractBean::DisplayName() {
        if (name.isEmpty()) {
            return DisplayAddress();
        }
        return name;
    }

    QString AbstractBean::DisplayTypeAndName() {
        return QStringLiteral("[%1] %2").arg(DisplayType(), DisplayName());
    }

    QString AbstractBean::DisplayCountry() {
        if (name.isEmpty())
            return QStringLiteral("未知");
            // 定义所有国家的名称列表
            QStringList countryList = {
                QStringLiteral("中国"),
                QStringLiteral("日本"),
                QStringLiteral("韩国"),
                QStringLiteral("朝鲜"),
                QStringLiteral("蒙古"),
                QStringLiteral("越南"),
                QStringLiteral("老挝"),
                QStringLiteral("柬埔寨"),
                QStringLiteral("缅甸"),
                QStringLiteral("泰国"),
                QStringLiteral("马来西亚"),
                QStringLiteral("新加坡"),
                QStringLiteral("印度尼西亚"),
                QStringLiteral("菲律宾"),
                QStringLiteral("文莱"),
                QStringLiteral("东帝汶"),
                QStringLiteral("尼泊尔"),
                QStringLiteral("不丹"),
                QStringLiteral("孟加拉国"),
                QStringLiteral("印度"),
                QStringLiteral("巴基斯坦"),
                QStringLiteral("斯里兰卡"),
                QStringLiteral("马尔代夫"),
                QStringLiteral("哈萨克斯坦"),
                QStringLiteral("吉尔吉斯斯坦"),
                QStringLiteral("塔吉克斯坦"),
                QStringLiteral("乌兹别克斯坦"),
                QStringLiteral("土库曼斯坦"),
                QStringLiteral("阿富汗"),
                QStringLiteral("伊拉克"),
                QStringLiteral("伊朗"),
                QStringLiteral("叙利亚"),
                QStringLiteral("约旦"),
                QStringLiteral("黎巴嫩"),
                QStringLiteral("以色列"),
                QStringLiteral("巴勒斯坦"),
                QStringLiteral("沙特阿拉伯"),
                QStringLiteral("巴林"),
                QStringLiteral("卡塔尔"),
                QStringLiteral("科威特"),
                QStringLiteral("阿联酋"),
                QStringLiteral("阿曼"),
                QStringLiteral("也门"),
                QStringLiteral("格鲁吉亚"),
                QStringLiteral("亚美尼亚"),
                QStringLiteral("阿塞拜疆"),
                QStringLiteral("土耳其"),
                QStringLiteral("塞浦路斯"),
                QStringLiteral("芬兰"),
                QStringLiteral("瑞典"),
                QStringLiteral("挪威"),
                QStringLiteral("冰岛"),
                QStringLiteral("丹麦"),
                QStringLiteral("爱沙尼亚"),
                QStringLiteral("拉脱维亚"),
                QStringLiteral("立陶宛"),
                QStringLiteral("白俄罗斯"),
                QStringLiteral("俄罗斯"),
                QStringLiteral("乌克兰"),
                QStringLiteral("波兰"),
                QStringLiteral("捷克"),
                QStringLiteral("斯洛伐克"),
                QStringLiteral("匈牙利"),
                QStringLiteral("德国"),
                QStringLiteral("奥地利"),
                QStringLiteral("瑞士"),
                QStringLiteral("列支敦士登"),
                QStringLiteral("英国"),
                QStringLiteral("爱尔兰"),
                QStringLiteral("荷兰"),
                QStringLiteral("比利时"),
                QStringLiteral("卢森堡"),
                QStringLiteral("法国"),
                QStringLiteral("摩纳哥"),
                QStringLiteral("意大利"),
                QStringLiteral("梵蒂冈"),
                QStringLiteral("圣马力诺"),
                QStringLiteral("马耳他"),
                QStringLiteral("西班牙"),
                QStringLiteral("葡萄牙"),
                QStringLiteral("安道尔"),
                QStringLiteral("希腊"),
                QStringLiteral("保加利亚"),
                QStringLiteral("罗马尼亚"),
                QStringLiteral("塞尔维亚"),
                QStringLiteral("克罗地亚"),
                QStringLiteral("斯洛文尼亚"),
                QStringLiteral("波黑"),
                QStringLiteral("黑山"),
                QStringLiteral("阿尔巴尼亚"),
                QStringLiteral("北马其顿"),
                QStringLiteral("埃及"),
                QStringLiteral("利比亚"),
                QStringLiteral("突尼斯"),
                QStringLiteral("阿尔及利亚"),
                QStringLiteral("摩洛哥"),
                QStringLiteral("苏丹"),
                QStringLiteral("南苏丹"),
                QStringLiteral("埃塞俄比亚"),
                QStringLiteral("厄立特里亚"),
                QStringLiteral("索马里"),
                QStringLiteral("吉布提"),
                QStringLiteral("肯尼亚"),
                QStringLiteral("坦桑尼亚"),
                QStringLiteral("乌干达"),
                QStringLiteral("卢旺达"),
                QStringLiteral("布隆迪"),
                QStringLiteral("塞舌尔"),
                QStringLiteral("乍得"),
                QStringLiteral("中非"),
                QStringLiteral("喀麦隆"),
                QStringLiteral("赤道几内亚"),
                QStringLiteral("加蓬"),
                QStringLiteral("刚果共和国"),
                QStringLiteral("刚果民主共和国"),
                QStringLiteral("圣多美和普林西比"),
                QStringLiteral("毛里塔尼亚"),
                QStringLiteral("塞内加尔"),
                QStringLiteral("冈比亚"),
                QStringLiteral("马里"),
                QStringLiteral("布基纳法索"),
                QStringLiteral("几内亚"),
                QStringLiteral("几内亚比绍"),
                QStringLiteral("佛得角"),
                QStringLiteral("塞拉利昂"),
                QStringLiteral("利比里亚"),
                QStringLiteral("科特迪瓦"),
                QStringLiteral("加纳"),
                QStringLiteral("多哥"),
                QStringLiteral("贝宁"),
                QStringLiteral("尼日尔"),
                QStringLiteral("尼日利亚"),
                QStringLiteral("赞比亚"),
                QStringLiteral("安哥拉"),
                QStringLiteral("津巴布韦"),
                QStringLiteral("马拉维"),
                QStringLiteral("莫桑比克"),
                QStringLiteral("博茨瓦纳"),
                QStringLiteral("纳米比亚"),
                QStringLiteral("南非"),
                QStringLiteral("斯威士兰"),
                QStringLiteral("莱索托"),
                QStringLiteral("马达加斯加"),
                QStringLiteral("科摩罗"),
                QStringLiteral("毛里求斯"),
                QStringLiteral("加拿大"),
                QStringLiteral("美国"),
                QStringLiteral("关岛"),
                QStringLiteral("墨西哥"),
                QStringLiteral("危地马拉"),
                QStringLiteral("伯利兹"),
                QStringLiteral("萨尔瓦多"),
                QStringLiteral("洪都拉斯"),
                QStringLiteral("尼加拉瓜"),
                QStringLiteral("哥斯达黎加"),
                QStringLiteral("巴拿马"),
                QStringLiteral("古巴"),
                QStringLiteral("牙买加"),
                QStringLiteral("海地"),
                QStringLiteral("多米尼加"),
                QStringLiteral("巴哈马"),
                QStringLiteral("巴巴多斯"),
                QStringLiteral("圣基茨和尼维斯"),
                QStringLiteral("圣卢西亚"),
                QStringLiteral("圣文森特和格林纳丁斯"),
                QStringLiteral("格林纳达"),
                QStringLiteral("特立尼达和多巴哥"),
                QStringLiteral("哥伦比亚"),
                QStringLiteral("委内瑞拉"),
                QStringLiteral("圭亚那"),
                QStringLiteral("苏里南"),
                QStringLiteral("厄瓜多尔"),
                QStringLiteral("秘鲁"),
                QStringLiteral("玻利维亚"),
                QStringLiteral("巴西"),
                QStringLiteral("智利"),
                QStringLiteral("阿根廷"),
                QStringLiteral("乌拉圭"),
                QStringLiteral("巴拉圭"),
                QStringLiteral("澳大利亚"),
                QStringLiteral("新西兰"),
                QStringLiteral("巴布亚新几内亚"),
                QStringLiteral("所罗门群岛"),
                QStringLiteral("瓦努阿图"),
                QStringLiteral("斐济"),
                QStringLiteral("基里巴斯"),
                QStringLiteral("瑙鲁"),
                QStringLiteral("密克罗尼西亚"),
                QStringLiteral("马绍尔群岛"),
                QStringLiteral("帕劳"),
                QStringLiteral("萨摩亚"),
                QStringLiteral("汤加"),
                QStringLiteral("图瓦卢"),
                QStringLiteral("台湾"),
                QStringLiteral("香港"),
                QStringLiteral("澳门"),
                QStringLiteral("科索沃"),
                QStringLiteral("西撒哈拉"),
                QStringLiteral("波多黎各"),
                QStringLiteral("南极"),
                QStringLiteral("格陵兰"),
                QStringLiteral("法属圭亚那")
            };

        // 遍历国家列表，判断代理名称中是否包含国家名称
        for (const QString &ct: countryList) {
            if (name.contains(ct)) {
                return ct;
            }
        }
        return QStringLiteral("未知");
    }

    void AbstractBean::ResolveDomainToIP(const std::function<void()> &onFinished) {
        bool noResolve = false;
        if (dynamic_cast<ChainBean *>(this) != nullptr) noResolve = true;
        if (dynamic_cast<CustomBean *>(this) != nullptr) noResolve = true;
        if (dynamic_cast<NaiveBean *>(this) != nullptr) noResolve = true;
        if (IsIpAddress(serverAddress)) noResolve = true;
        if (noResolve) {
            onFinished();
            return;
        }

#if QT_VERSION >= QT_VERSION_CHECK(5, 11, 0) // TODO older QT
        QHostInfo::lookupHost(serverAddress, QApplication::instance(), [=](const QHostInfo &host) {
            auto addr = host.addresses();
            if (!addr.isEmpty()) {
                auto domain = serverAddress;
                auto stream = GetStreamSettings(this);

                // replace serverAddress
                serverAddress = addr.first().toString();

                // replace ws tls
                if (stream != nullptr) {
                    if (stream->security == "tls" && stream->sni.isEmpty()) {
                        stream->sni = domain;
                    }
                    if (stream->network == "ws" && stream->host.isEmpty()) {
                        stream->host = domain;
                    }
                }
            }
            onFinished();
        });
#endif
    }
} // namespace NekoGui_fmt
