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

function testSplitStr()
    local ary = el.splitStr("seperated by space e sp ", " ")
    print("el## return type of splitStr(): " .. type(ary))
    if type(ary) == "table" then
        for i=1, #ary do
            print(ary[i])
        end
    end
end

function testSplitStrSTL()
    local ary = el.splitStrUsingSTL("seperated by space e sp ", " ")
    print("el## return type of splitStrUsingSTL(): " .. type(ary))
    if type(ary) == "table" then
        for i=1, #ary do
            print(ary[i])
        end
    end
end

testListdir()

testMapArray()

testSplitStr()

testSplitStrSTL()

function testTuple()
    x = tuple.new(100, "hello", {}, 30)
    print(x(1))
    print(x(2))
    print(x(3))
    print(x())
end

function backsoon()
    local s = "i am busy developing my own games recently, so maybe i will not log in github everyday"
    local d22 = "decide to use cocos code ide and quick to develop the game, and vim as the code editor"
    return s
end
