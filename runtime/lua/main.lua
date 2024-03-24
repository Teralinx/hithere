package.path = "./lua/htmlparser/?.lua;" .. package.path;
local htmlparser = require("htmlparser");




ip = nil;
 function iteratedom(dom)
    if "input" == dom.name then
        if dom.attributes.id and "address" == dom.attributes.id and dom.attributes.value then
            ip =  dom.attributes.value;
        end
    end
    if nil == ip then
        for i,v in ipairs(dom.nodes) do
            iteratedom(v);
        end
    end
end

function searchip(rawhtml)
    iteratedom(htmlparser.parse(rawhtml));
end

function getip()
    print(ip);
    return ip;
end

