local overview = 
[[
    LIB_NAME        : debug
    "getinfo"       : call with a function or with a number indicating the stack level.
                    : return a table of decription of the arg.
                    : notice: low efficiency, use second arg to specified concrete info you need.
    "traceback"     : return a traceback string.
    "getlocal"      : getlocal variable info
    "getupvalue"    : get non-local variable info
    "sethook"       :
]]

local debugLibTest = { 
    cases = {} 
}

local traceback = function()
    for level=1, math.huge do
        local info = debug.getinfo(level, "Sl")
        if not info then
            break
        end
        if info.what == "C" then
            print(level, "C function")
        else
            print(string.format("[%s]: %d", info.short_src, info.currentline))
        end
    end
end

debugLibTest.cases["getinfo"] = 
{
    f = function()
        traceback(traceback)
    end
}

debugLibTest.cases["traceback"] = {
    f = function()
        local traceStr = debug.traceback()
        print("traceStr: " .. tostring(traceStr))
    end
}

debugLibTest.cases["getlocal"] = {
    f = function(a, b)
        local x
        do local c = a -b end
        while true do
            local name, value = debug.getlocal(1, a)
            if not name then
                break
            end
            print(name, value)
            a = a + 1
        end
    end,
    args = {10, 20}
}

debugLibTest.cases["getupvalue"] = {
    f = function(name)
        local val, found 

        -- try local
        for i=1,math.huge do
            local n, v = debug.getlocal(2, i)
            if not n then break end
            if n == name then
                val = v
                found = true
            end
        end
        if found then
            return val
        end

        -- try non-local 
        local func = debug.getinfo(2, "f").func
        for i=1, math.huge do
            local n, v = debug.getupvalue(func, i)
            if not n then
                break
            end
            if n == name then
                return v
            end
        end

        -- still not found, try env.
        return getfenv(func)[name]
    end,
    -- args = {"traceback"}
    -- args = {"overview"}
    args = {"valForUpvalue"} -- defined in the debugLibTest.test function 
}

debugLibTest.cases["trace coroutine"] = {
    f = function()
        co = coroutine.create(function()
            local x = 10
            coroutine.yield()
            error("some error")
        end)

        coroutine.resume(co)
        print(debug.traceback(co))
    end
}

debugLibTest.cases["sethook"] = {
    f = function()
        debug.sethook(print, "l")
        print("hello world")
        print("hello world")
        print("hello world")
        print("hello world")
        print("hello world")
    end
}

-- how to print vaargs 
local ap = function(val)
    if type(val) == "table" then
        for i=1, #val do
            print(string.format("[%d] = %s", i, tostring(val[i])))
        end
    else
        print(tostring(val))
    end
end

debugLibTest.test = function(self)
    for k,case in pairs(self.cases) do
        if not case.skip then
            print(string.format("===================== case: %s =====================", k))
            if type(case.f) ~= "function"  then
                print(string.format("-- skip case: %s, not a function", k))
            else
                local ret
                local valForUpvalue = 101
                if case.args then
                    print("call with args: " .. unpack(case.args))
                    ret = case.f(unpack(case.args))
                else
                    ret = case.f()
                end
                print("----------ret:")
                ap(ret);
            end
            print(string.format("===================== end of case: %s =====================\n", k))
        end
    end
end


debugLibTest.cases["getinfo"].skip    = false

debugLibTest:test()

local tt=function(name)
    local val, found 

    -- try local
    for i=1,math.huge do
        local n, v = debug.getlocal(2, i)
        if not n then break end
        if n == name then
            val = v
            found = true
        end
    end
    if found then
        return val
    end

    -- try non-local 
    local func = debug.getinfo(2, "f").func
    for i=1, math.huge do
        local n, v = debug.getupvalue(func, i)
        if not n then
            break
        end
        if n == name then
            return v
        end
    end

    -- still not found, try env.
    return getfenv(func)[name]
end

