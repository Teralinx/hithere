package.path = "./lua/htmlparser/?.lua;" .. package.path;
local htmlparser = require("htmlparser");

function accessWebAddr()
    return "https://ip.tool.chinaz.com/";
end

 function iteratedom(dom)
    local ip;
    if "input" == dom.name then
        if dom.attributes.id and "address" == dom.attributes.id and dom.attributes.value then
            ip =  dom.attributes.value;
        end
    end
    if nil == ip then
        for i,v in ipairs(dom.nodes) do
            ip = iteratedom(v);
            if ip then
                break;
            end
        end
    end
    return ip;
end

function getip(rawhtml)
    local ip = iteratedom(htmlparser.parse(rawhtml,10000));
    return ip;
end



