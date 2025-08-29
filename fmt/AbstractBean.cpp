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
        _add(new configItem("remark", &remark, itemType::string));
    }

    void AbstractBean::SetCountryFromDisplay() {
        this->remark = this->name;
        this->name = DisplayCountry();
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

        // 定义国家代码到中文名称的映射
        QMap<QString, QString> codeToChineseName = {
            {"CN", "中国"},
            {"JP", "日本"},
            {"KR", "韩国"},
            {"KP", "朝鲜"},
            {"MN", "蒙古"},
            {"VN", "越南"},
            {"LA", "老挝"},
            {"KH", "柬埔寨"},
            {"MM", "缅甸"},
            {"TH", "泰国"},
            {"MY", "马来西亚"},
            {"SG", "新加坡"},
            {"ID", "印度尼西亚"},
            {"PH", "菲律宾"},
            {"BN", "文莱"},
            {"TL", "东帝汶"},
            {"NP", "尼泊尔"},
            {"BT", "不丹"},
            {"BD", "孟加拉"},
            {"IN", "印度"},
            {"PK", "巴基斯坦"},
            {"LK", "斯里兰卡"},
            {"MV", "马尔代夫"},
            {"KZ", "哈萨克斯坦"},
            {"KG", "吉尔吉斯斯坦"},
            {"TJ", "塔吉克斯坦"},
            {"UZ", "乌兹别克斯坦"},
            {"TM", "土库曼斯坦"},
            {"AF", "阿富汗"},
            {"IQ", "伊拉克"},
            {"IR", "伊朗"},
            {"SY", "叙利亚"},
            {"JO", "约旦"},
            {"LB", "黎巴嫩"},
            {"IL", "以色列"},
            {"PS", "巴勒斯坦"},
            {"SA", "沙特阿拉伯"},
            {"BH", "巴林"},
            {"QA", "卡塔尔"},
            {"KW", "科威特"},
            {"AE", "阿联酋"},
            {"OM", "阿曼"},
            {"YE", "也门"},
            {"GE", "格鲁吉亚"},
            {"AM", "亚美尼亚"},
            {"AZ", "阿塞拜疆"},
            {"TR", "土耳其"},
            {"CY", "塞浦路斯"},
            {"FI", "芬兰"},
            {"SE", "瑞典"},
            {"NO", "挪威"},
            {"IS", "冰岛"},
            {"DK", "丹麦"},
            {"EE", "爱沙尼亚"},
            {"LV", "拉脱维亚"},
            {"LT", "立陶宛"},
            {"BY", "白俄罗斯"},
            {"RU", "俄罗斯"},
            {"UA", "乌克兰"},
            {"PL", "波兰"},
            {"CZ", "捷克"},
            {"SK", "斯洛伐克"},
            {"HU", "匈牙利"},
            {"DE", "德国"},
            {"AT", "奥地利"},
            {"CH", "瑞士"},
            {"LI", "列支敦士登"},
            {"GB", "英国"},
            {"IE", "爱尔兰"},
            {"NL", "荷兰"},
            {"BE", "比利时"},
            {"LU", "卢森堡"},
            {"FR", "法国"},
            {"MC", "摩纳哥"},
            {"IT", "意大利"},
            {"VA", "梵蒂冈"},
            {"SM", "圣马力诺"},
            {"MT", "马耳他"},
            {"ES", "西班牙"},
            {"PT", "葡萄牙"},
            {"AD", "安道尔"},
            {"GR", "希腊"},
            {"BG", "保加利亚"},
            {"RO", "罗马尼亚"},
            {"RS", "塞尔维亚"},
            {"HR", "克罗地亚"},
            {"SI", "斯洛文尼亚"},
            {"BA", "波黑"},
            {"ME", "黑山"},
            {"AL", "阿尔巴尼亚"},
            {"MK", "北马其顿"},
            {"EG", "埃及"},
            {"LY", "利比亚"},
            {"TN", "突尼斯"},
            {"DZ", "阿尔及利亚"},
            {"MA", "摩洛哥"},
            {"SD", "苏丹"},
            {"SS", "南苏丹"},
            {"ET", "埃塞俄比亚"},
            {"ER", "厄立特里亚"},
            {"SO", "索马里"},
            {"DJ", "吉布提"},
            {"KE", "肯尼亚"},
            {"TZ", "坦桑尼亚"},
            {"UG", "乌干达"},
            {"RW", "卢旺达"},
            {"BI", "布隆迪"},
            {"SC", "塞舌尔"},
            {"TD", "乍得"},
            {"CF", "中非"},
            {"CM", "喀麦隆"},
            {"GQ", "赤道几内亚"},
            {"GA", "加蓬"},
            {"CG", "刚果共和国"},
            {"CD", "刚果民主共和国"},
            {"ST", "圣多美和普林西比"},
            {"MR", "毛里塔尼亚"},
            {"SN", "塞内加尔"},
            {"GM", "冈比亚"},
            {"ML", "马里"},
            {"BF", "布基纳法索"},
            {"GN", "几内亚"},
            {"GW", "几内亚比绍"},
            {"CV", "佛得角"},
            {"SL", "塞拉利昂"},
            {"LR", "利比里亚"},
            {"CI", "科特迪瓦"},
            {"GH", "加纳"},
            {"TG", "多哥"},
            {"BJ", "贝宁"},
            {"NE", "尼日尔"},
            {"NG", "尼日利亚"},
            {"ZM", "赞比亚"},
            {"AO", "安哥拉"},
            {"ZW", "津巴布韦"},
            {"MW", "马拉维"},
            {"MZ", "莫桑比克"},
            {"BW", "博茨瓦纳"},
            {"NA", "纳米比亚"},
            {"ZA", "南非"},
            {"SZ", "斯威士兰"},
            {"LS", "莱索托"},
            {"MG", "马达加斯加"},
            {"KM", "科摩罗"},
            {"MU", "毛里求斯"},
            {"CA", "加拿大"},
            {"US", "美国"},
            {"GU", "关岛"},
            {"MX", "墨西哥"},
            {"GT", "危地马拉"},
            {"BZ", "伯利兹"},
            {"SV", "萨尔瓦多"},
            {"HN", "洪都拉斯"},
            {"NI", "尼加拉瓜"},
            {"CR", "哥斯达黎加"},
            {"PA", "巴拿马"},
            {"CU", "古巴"},
            {"JM", "牙买加"},
            {"HT", "海地"},
            {"DO", "多米尼加"},
            {"BS", "巴哈马"},
            {"BB", "巴巴多斯"},
            {"KN", "圣基茨和尼维斯"},
            {"LC", "圣卢西亚"},
            {"VC", "圣文森特和格林纳丁斯"},
            {"GD", "格林纳达"},
            {"TT", "特立尼达和多巴哥"},
            {"CO", "哥伦比亚"},
            {"VE", "委内瑞拉"},
            {"GY", "圭亚那"},
            {"SR", "苏里南"},
            {"EC", "厄瓜多尔"},
            {"PE", "秘鲁"},
            {"BO", "玻利维亚"},
            {"BR", "巴西"},
            {"CL", "智利"},
            {"AR", "阿根廷"},
            {"UY", "乌拉圭"},
            {"PY", "巴拉圭"},
            {"AU", "澳大利亚"},
            {"NZ", "新西兰"},
            {"PG", "巴布亚新几内亚"},
            {"SB", "所罗门群岛"},
            {"VU", "瓦努阿图"},
            {"FJ", "斐济"},
            {"KI", "基里巴斯"},
            {"NR", "瑙鲁"},
            {"FM", "密克罗尼西亚"},
            {"MH", "马绍尔群岛"},
            {"PW", "帕劳"},
            {"WS", "萨摩亚"},
            {"TO", "汤加"},
            {"TV", "图瓦卢"},
            {"TW", "台湾"},
            {"HK", "香港"},
            {"MO", "澳门"},
            {"XK", "科索沃"},
            {"EH", "西撒哈拉"},
            {"PR", "波多黎各"},
            {"AQ", "南极"},
            {"GL", "格陵兰"},
            {"RE", "留尼汪"},
            {"GF", "法属圭亚那"},
            {"PF", "法属波利尼西亚"},
            {"MF", "法属圣马丁"},
            {"PM", "圣皮埃尔和密克隆群岛"},
        };

        // 定义所有国家的名称和代码的映射
        QMap<QString, QString> countryMap = {
            {QStringLiteral("日本"), "JP"},
            {QStringLiteral("韩国"), "KR"},
            {QStringLiteral("朝鲜"), "KP"},
            {QStringLiteral("蒙古"), "MN"},
            {QStringLiteral("越南"), "VN"},
            {QStringLiteral("老挝"), "LA"},
            {QStringLiteral("柬埔寨"), "KH"},
            {QStringLiteral("缅甸"), "MM"},
            {QStringLiteral("泰国"), "TH"},
            {QStringLiteral("马来西亚"), "MY"},
            {QStringLiteral("新加坡"), "SG"},
            {QStringLiteral("印度尼西亚"), "ID"},
            {QStringLiteral("菲律宾"), "PH"},
            {QStringLiteral("文莱"), "BN"},
            {QStringLiteral("东帝汶"), "TL"},
            {QStringLiteral("尼泊尔"), "NP"},
            {QStringLiteral("不丹"), "BT"},
            {QStringLiteral("孟加拉"), "BD"},
            {QStringLiteral("印度"), "IN"},
            {QStringLiteral("巴基斯坦"), "PK"},
            {QStringLiteral("斯里兰卡"), "LK"},
            {QStringLiteral("马尔代夫"), "MV"},
            {QStringLiteral("哈萨克斯坦"), "KZ"},
            {QStringLiteral("吉尔吉斯斯坦"), "KG"},
            {QStringLiteral("塔吉克斯坦"), "TJ"},
            {QStringLiteral("乌兹别克斯坦"), "UZ"},
            {QStringLiteral("土库曼斯坦"), "TM"},
            {QStringLiteral("阿富汗"), "AF"},
            {QStringLiteral("伊拉克"), "IQ"},
            {QStringLiteral("伊朗"), "IR"},
            {QStringLiteral("叙利亚"), "SY"},
            {QStringLiteral("约旦"), "JO"},
            {QStringLiteral("黎巴嫩"), "LB"},
            {QStringLiteral("以色列"), "IL"},
            {QStringLiteral("巴勒斯坦"), "PS"},
            {QStringLiteral("沙特阿拉伯"), "SA"},
            {QStringLiteral("巴林"), "BH"},
            {QStringLiteral("卡塔尔"), "QA"},
            {QStringLiteral("科威特"), "KW"},
            {QStringLiteral("阿联酋"), "AE"},
            {QStringLiteral("阿曼"), "OM"},
            {QStringLiteral("也门"), "YE"},
            {QStringLiteral("格鲁吉亚"), "GE"},
            {QStringLiteral("亚美尼亚"), "AM"},
            {QStringLiteral("阿塞拜疆"), "AZ"},
            {QStringLiteral("土耳其"), "TR"},
            {QStringLiteral("塞浦路斯"), "CY"},
            {QStringLiteral("芬兰"), "FI"},
            {QStringLiteral("瑞典"), "SE"},
            {QStringLiteral("挪威"), "NO"},
            {QStringLiteral("冰岛"), "IS"},
            {QStringLiteral("丹麦"), "DK"},
            {QStringLiteral("爱沙尼亚"), "EE"},
            {QStringLiteral("拉脱维亚"), "LV"},
            {QStringLiteral("立陶宛"), "LT"},
            {QStringLiteral("白俄罗斯"), "BY"},
            {QStringLiteral("俄罗斯"), "RU"},
            {QStringLiteral("乌克兰"), "UA"},
            {QStringLiteral("波兰"), "PL"},
            {QStringLiteral("捷克"), "CZ"},
            {QStringLiteral("斯洛伐克"), "SK"},
            {QStringLiteral("匈牙利"), "HU"},
            {QStringLiteral("德国"), "DE"},
            {QStringLiteral("奥地利"), "AT"},
            {QStringLiteral("瑞士"), "CH"},
            {QStringLiteral("列支敦士登"), "LI"},
            {QStringLiteral("英国"), "GB"},
            {QStringLiteral("爱尔兰"), "IE"},
            {QStringLiteral("荷兰"), "NL"},
            {QStringLiteral("比利时"), "BE"},
            {QStringLiteral("卢森堡"), "LU"},
            {QStringLiteral("法国"), "FR"},
            {QStringLiteral("摩纳哥"), "MC"},
            {QStringLiteral("意大利"), "IT"},
            {QStringLiteral("梵蒂冈"), "VA"},
            {QStringLiteral("圣马力诺"), "SM"},
            {QStringLiteral("马耳他"), "MT"},
            {QStringLiteral("西班牙"), "ES"},
            {QStringLiteral("葡萄牙"), "PT"},
            {QStringLiteral("安道尔"), "AD"},
            {QStringLiteral("希腊"), "GR"},
            {QStringLiteral("保加利亚"), "BG"},
            {QStringLiteral("罗马尼亚"), "RO"},
            {QStringLiteral("塞尔维亚"), "RS"},
            {QStringLiteral("克罗地亚"), "HR"},
            {QStringLiteral("斯洛文尼亚"), "SI"},
            {QStringLiteral("波黑"), "BA"},
            {QStringLiteral("黑山"), "ME"},
            {QStringLiteral("阿尔巴尼亚"), "AL"},
            {QStringLiteral("北马其顿"), "MK"},
            {QStringLiteral("埃及"), "EG"},
            {QStringLiteral("利比亚"), "LY"},
            {QStringLiteral("突尼斯"), "TN"},
            {QStringLiteral("阿尔及利亚"), "DZ"},
            {QStringLiteral("摩洛哥"), "MA"},
            {QStringLiteral("苏丹"), "SD"},
            {QStringLiteral("南苏丹"), "SS"},
            {QStringLiteral("埃塞俄比亚"), "ET"},
            {QStringLiteral("厄立特里亚"), "ER"},
            {QStringLiteral("索马里"), "SO"},
            {QStringLiteral("吉布提"), "DJ"},
            {QStringLiteral("肯尼亚"), "KE"},
            {QStringLiteral("坦桑尼亚"), "TZ"},
            {QStringLiteral("乌干达"), "UG"},
            {QStringLiteral("卢旺达"), "RW"},
            {QStringLiteral("布隆迪"), "BI"},
            {QStringLiteral("塞舌尔"), "SC"},
            {QStringLiteral("乍得"), "TD"},
            {QStringLiteral("中非"), "CF"},
            {QStringLiteral("喀麦隆"), "CM"},
            {QStringLiteral("赤道几内亚"), "GQ"},
            {QStringLiteral("加蓬"), "GA"},
            {QStringLiteral("刚果共和国"), "CG"},
            {QStringLiteral("刚果民主共和国"), "CD"},
            {QStringLiteral("圣多美和普林西比"), "ST"},
            {QStringLiteral("毛里塔尼亚"), "MR"},
            {QStringLiteral("塞内加尔"), "SN"},
            {QStringLiteral("冈比亚"), "GM"},
            {QStringLiteral("马里"), "ML"},
            {QStringLiteral("布基纳法索"), "BF"},
            {QStringLiteral("几内亚"), "GN"},
            {QStringLiteral("几内亚比绍"), "GW"},
            {QStringLiteral("佛得角"), "CV"},
            {QStringLiteral("塞拉利昂"), "SL"},
            {QStringLiteral("利比里亚"), "LR"},
            {QStringLiteral("科特迪瓦"), "CI"},
            {QStringLiteral("加纳"), "GH"},
            {QStringLiteral("多哥"), "TG"},
            {QStringLiteral("贝宁"), "BJ"},
            {QStringLiteral("尼日尔"), "NE"},
            {QStringLiteral("尼日利亚"), "NG"},
            {QStringLiteral("赞比亚"), "ZM"},
            {QStringLiteral("安哥拉"), "AO"},
            {QStringLiteral("津巴布韦"), "ZW"},
            {QStringLiteral("马拉维"), "MW"},
            {QStringLiteral("莫桑比克"), "MZ"},
            {QStringLiteral("博茨瓦纳"), "BW"},
            {QStringLiteral("纳米比亚"), "NA"},
            {QStringLiteral("南非"), "ZA"},
            {QStringLiteral("斯威士兰"), "SZ"},
            {QStringLiteral("莱索托"), "LS"},
            {QStringLiteral("马达加斯加"), "MG"},
            {QStringLiteral("科摩罗"), "KM"},
            {QStringLiteral("毛里求斯"), "MU"},
            {QStringLiteral("加拿大"), "CA"},
            {QStringLiteral("美国"), "US"},
            {QStringLiteral("关岛"), "GU"},
            {QStringLiteral("墨西哥"), "MX"},
            {QStringLiteral("危地马拉"), "GT"},
            {QStringLiteral("伯利兹"), "BZ"},
            {QStringLiteral("萨尔瓦多"), "SV"},
            {QStringLiteral("洪都拉斯"), "HN"},
            {QStringLiteral("尼加拉瓜"), "NI"},
            {QStringLiteral("哥斯达黎加"), "CR"},
            {QStringLiteral("巴拿马"), "PA"},
            {QStringLiteral("古巴"), "CU"},
            {QStringLiteral("牙买加"), "JM"},
            {QStringLiteral("海地"), "HT"},
            {QStringLiteral("多米尼加"), "DO"},
            {QStringLiteral("巴哈马"), "BS"},
            {QStringLiteral("巴巴多斯"), "BB"},
            {QStringLiteral("圣基茨和尼维斯"), "KN"},
            {QStringLiteral("圣卢西亚"), "LC"},
            {QStringLiteral("圣文森特和格林纳丁斯"), "VC"},
            {QStringLiteral("格林纳达"), "GD"},
            {QStringLiteral("特立尼达和多巴哥"), "TT"},
            {QStringLiteral("哥伦比亚"), "CO"},
            {QStringLiteral("委内瑞拉"), "VE"},
            {QStringLiteral("圭亚那"), "GY"},
            {QStringLiteral("苏里南"), "SR"},
            {QStringLiteral("厄瓜多尔"), "EC"},
            {QStringLiteral("秘鲁"), "PE"},
            {QStringLiteral("玻利维亚"), "BO"},
            {QStringLiteral("巴西"), "BR"},
            {QStringLiteral("智利"), "CL"},
            {QStringLiteral("阿根廷"), "AR"},
            {QStringLiteral("乌拉圭"), "UY"},
            {QStringLiteral("巴拉圭"), "PY"},
            {QStringLiteral("澳大利亚"), "AU"},
            {QStringLiteral("新西兰"), "NZ"},
            {QStringLiteral("巴布亚新几内亚"), "PG"},
            {QStringLiteral("所罗门群岛"), "SB"},
            {QStringLiteral("瓦努阿图"), "VU"},
            {QStringLiteral("斐济"), "FJ"},
            {QStringLiteral("基里巴斯"), "KI"},
            {QStringLiteral("瑙鲁"), "NR"},
            {QStringLiteral("密克罗尼西亚"), "FM"},
            {QStringLiteral("马绍尔群岛"), "MH"},
            {QStringLiteral("帕劳"), "PW"},
            {QStringLiteral("萨摩亚"), "WS"},
            {QStringLiteral("汤加"), "TO"},
            {QStringLiteral("图瓦卢"), "TV"},
            {QStringLiteral("台湾"), "TW"},
            {QStringLiteral("香港"), "HK"},
            {QStringLiteral("澳门"), "MO"},
            {QStringLiteral("科索沃"), "XK"},
            {QStringLiteral("西撒哈拉"), "EH"},
            {QStringLiteral("波多黎各"), "PR"},
            {QStringLiteral("南极"), "AQ"},
            {QStringLiteral("格陵兰"), "GL"},
            {QStringLiteral("留尼汪"), "RE"},
            {QStringLiteral("法属圭亚那"), "GF"},
            {QStringLiteral("法属波利尼西亚"), "PF"},
            {QStringLiteral("法属圣马丁"), "MF"},
            {QStringLiteral("圣皮埃尔和密克隆群岛"), "PM"},
            // 国旗emoji识别
            {QStringLiteral("🇭🇰"), "HK"},
            {QStringLiteral("🇺🇸"), "US"},
            {QStringLiteral("🇯🇵"), "JP"},
            {QStringLiteral("🇷🇺"), "RU"},
            {QStringLiteral("🇨🇭"), "CH"},
            {QStringLiteral("🇫🇷"), "FR"},
            {QStringLiteral("🇬🇧"), "GB"},
            {QStringLiteral("🇸🇬"), "SG"},
            {QStringLiteral("🇰🇷"), "KR"},
            {QStringLiteral("🇩🇪"), "DE"},
            {QStringLiteral("🇮🇹"), "IT"},
            {QStringLiteral("🇪🇸"), "ES"},
            {QStringLiteral("🇨🇦"), "CA"},
            {QStringLiteral("🇦🇺"), "AU"},
            {QStringLiteral("🇧🇷"), "BR"},
            {QStringLiteral("🇮🇳"), "IN"},
            {QStringLiteral("🇹🇼"), "TW"},
            {QStringLiteral("🇲🇴"), "MO"},
            {QStringLiteral("🇹🇭"), "TH"},
            {QStringLiteral("🇲🇾"), "MY"},
            {QStringLiteral("🇮🇩"), "ID"},
            {QStringLiteral("🇵🇭"), "PH"},
            {QStringLiteral("🇻🇳"), "VN"},
            {QStringLiteral("🇳🇱"), "NL"},
            {QStringLiteral("🇸🇪"), "SE"},
            {QStringLiteral("🇳🇴"), "NO"},
            {QStringLiteral("🇫🇮"), "FI"},
            {QStringLiteral("🇩🇰"), "DK"},
            {QStringLiteral("🇦🇹"), "AT"},
            {QStringLiteral("🇵🇱"), "PL"},
            {QStringLiteral("🇹🇷"), "TR"},
            {QStringLiteral("🇺🇦"), "UA"},
            {QStringLiteral("🇮🇪"), "IE"},
            {QStringLiteral("🇧🇪"), "BE"},
            {QStringLiteral("🇵🇹"), "PT"},
            {QStringLiteral("🇬🇷"), "GR"},
            {QStringLiteral("🇿🇦"), "ZA"},
            {QStringLiteral("🇪🇬"), "EG"},
            {QStringLiteral("🇮🇱"), "IL"},
            {QStringLiteral("🇸🇦"), "SA"},
            {QStringLiteral("🇦🇪"), "AE"},
            {QStringLiteral("🇲🇽"), "MX"},
            {QStringLiteral("🇦🇷"), "AR"},
            {QStringLiteral("🇨🇱"), "CL"},
            {QStringLiteral("🇳🇿"), "NZ"},
            {QStringLiteral("🇮🇸"), "IS"},
            {QStringLiteral("🇱🇺"), "LU"},
            {QStringLiteral("🇨🇿"), "CZ"},
            {QStringLiteral("🇭🇺"), "HU"},
            {QStringLiteral("🇷🇴"), "RO"},
            {QStringLiteral("🇧🇬"), "BG"},
            {QStringLiteral("🇭🇷"), "HR"},
            {QStringLiteral("🇸🇮"), "SI"},
            {QStringLiteral("🇸🇰"), "SK"},
            {QStringLiteral("🇱🇹"), "LT"},
            {QStringLiteral("🇱🇻"), "LV"},
            {QStringLiteral("🇪🇪"), "EE"},
            // 英文国家名称识别
            {"Hong Kong", "HK"},
            {"HongKong", "HK"},
            {"United States", "US"},
            {"USA", "US"},
            {"America", "US"},
            {"Japan", "JP"},
            {"Russia", "RU"},
            {"Russian", "RU"},
            {"Switzerland", "CH"},
            {"France", "FR"},
            {"French", "FR"},
            {"United Kingdom", "GB"},
            {"UK", "GB"},
            {"Britain", "GB"},
            {"England", "GB"},
            {"Singapore", "SG"},
            {"Korea", "KR"},
            {"South Korea", "KR"},
            {"Germany", "DE"},
            {"German", "DE"},
            {"Italy", "IT"},
            {"Italian", "IT"},
            {"Spain", "ES"},
            {"Spanish", "ES"},
            {"Canada", "CA"},
            {"Canadian", "CA"},
            {"Australia", "AU"},
            {"Australian", "AU"},
            {"Brazil", "BR"},
            {"Brazilian", "BR"},
            {"India", "IN"},
            {"Indian", "IN"},
            {"Taiwan", "TW"},
            {"Macau", "MO"},
            {"Macao", "MO"},
            {"Thailand", "TH"},
            {"Thai", "TH"},
            {"Malaysia", "MY"},
            {"Indonesian", "ID"},
            {"Philippines", "PH"},
            {"Vietnam", "VN"},
            {"Vietnamese", "VN"},
            {"Netherlands", "NL"},
            {"Holland", "NL"},
            {"Dutch", "NL"},
            {"Sweden", "SE"},
            {"Swedish", "SE"},
            {"Norway", "NO"},
            {"Norwegian", "NO"},
            {"Finland", "FI"},
            {"Finnish", "FI"},
            {"Denmark", "DK"},
            {"Danish", "DK"},
            {"Austria", "AT"},
            {"Austrian", "AT"},
            {"Poland", "PL"},
            {"Polish", "PL"},
            {"Turkey", "TR"},
            {"Turkish", "TR"},
            {"Ukraine", "UA"},
            {"Ukrainian", "UA"},
            {"Ireland", "IE"},
            {"Irish", "IE"},
            {"Belgium", "BE"},
            {"Belgian", "BE"},
            {"Portugal", "PT"},
            {"Portuguese", "PT"},
            {"Greece", "GR"},
            {"Greek", "GR"},
            {"South Africa", "ZA"},
            {"Egypt", "EG"},
            {"Egyptian", "EG"},
            {"Israel", "IL"},
            {"Israeli", "IL"},
            {"Saudi Arabia", "SA"},
            {"UAE", "AE"},
            {"Mexico", "MX"},
            {"Mexican", "MX"},
            {"Argentina", "AR"},
            {"Chilean", "CL"},
            {"New Zealand", "NZ"},
            {"Iceland", "IS"},
            // 地区别名
            // 简化名称映射（只保留不会误匹配的）
            {"港", "HK"},
            {"台湾", "TW"},
            {"巴西", "BR"},
            {"澳门", "MO"},
            {"瑞典", "SE"},
            {"爱尔兰", "IE"},
            {"南非", "ZA"},
            {"埃及", "EG"},
            {"沙特", "SA"},
            {"阿联酋", "AE"},
            {"阿根廷", "AR"},
            {"智利", "CL"},
            {"新西兰", "NZ"},
            {"冰岛", "IS"},
        };

        // 创建名称的大小写不敏感版本用于匹配
        QString nameLower = name.toLower();
        QString nameUpper = name.toUpper();
        
        // 特殊处理印度（单独处理避免与印度尼西亚冲突）
        if (name.contains(QStringLiteral("印度")) && !name.contains(QStringLiteral("印度尼西亚"))) {
            return QStringLiteral("印度(IN)");
        }
        
        // 遍历国家映射，寻找匹配项
        for (auto it = countryMap.begin(); it != countryMap.end(); ++it) {
            QString key = it.key();
            QString code = it.value();
            
            bool matched = false;
            
            // 直接匹配（包含emoji和中文）
            if (name.contains(key)) {
                matched = true;
            }
            // 大小写不敏感的英文匹配
            else if (key.at(0).isLetter()) {
                if (nameLower.contains(key.toLower()) || nameUpper.contains(key.toUpper())) {
                    matched = true;
                }
            }
            
            if (matched) {
                // 返回统一格式：中文名称 + 代码
                QString chineseName = codeToChineseName.value(code, "");
                // 构建返回字符串
                QString result = chineseName;
                result += " (" + code + ")";
                return result;
            }
        }
        
        return QStringLiteral("未知");
    } // Removed the extra closing brace that was here

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
