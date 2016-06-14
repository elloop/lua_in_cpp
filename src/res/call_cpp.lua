package.cpath = package.cpath .. ";../lib/?.so"

local el = require "ellua"         -- dynamic load libellua.so under ../lib/ 


function testListdir()
    local cd = "."
    local x = el.listdir(cd)
    
    print("ret type of el.listdir(): " .. type(x))

    if type(x) == "table" then
        print("dir: " .. tostring(cd))
        for k,v in pairs(x) do
            print(v)
        end
    end
end

function testMapArray()
    local ary = {1, 2, 3, 4, 5, 6}
    print(ary)
    for index=1, #ary do
        print(ary[index])
    end
    el.mapArray(ary, function(arg)
        return arg * 2
    end)
    print("el## after mapArray oper:")
    for index=1, #ary do
        print(ary[index])
    end
end

testListdir()
testMapArray()

