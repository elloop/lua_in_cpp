local overview = 
[[
    LIB_NAME     : debug
    "getinfo"    : call with a function or with a number indicating the stack level.
                 : return a table of decription of the arg.
                 : notice: low efficiency, use second arg to specified concrete info you need.
    "traceback"  : return a traceback string.
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

debugLibTest.test = function(self)
    for k,case in pairs(self.cases) do
        if not case.skip then
            print(string.format("===================== case: %s =====================", k))
            if type(case.f) ~= "function"  then
                print(string.format("-- skip case: %s, not a function", k))
            else
                if case.args then
                    print("call with args: " .. unpack(case.args))
                    case.f(unpack(case.args))
                else
                    case.f()
                end
            end
            print(string.format("===================== end of case: %s =====================\n", k))
        end
    end
end

debugLibTest.cases["getinfo"].skip    = false

debugLibTest:test()

