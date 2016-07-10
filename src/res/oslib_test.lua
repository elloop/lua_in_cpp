local overview = 
[[
    "time"    : date to number , return a number.
    "date"    : number to date, 2 forms. return a table or a string
    "clock"   : calculate run time in seconds
    "getenv"  :
    "execute" :
]]

local oslibTest = {
    cases = {},
    registerCase = function(self, case)
        self.cases[case.key] = case
    end
}


oslibTest:registerCase(
    {
        key = "time",

        f = function()
            local timeTable = { year=1970, month=1, day=1, hour=0 }
            local tval = os.time(timeTable)
            print("el## tval: " .. tval) -- -28800  (utf+8, 8 * 3600 == 28800) 
        end
    }
)

oslibTest:registerCase(
    {
        key = "date",

        f = function()
            local tval = -28800
            local timeTable = os.date("*t", tval)
            for k,v in pairs(timeTable) do
                print(string.format("%s: %s", tostring(k), tostring(v)))
            end
            --[[
            hour: 0
            min: 0
            wday: 5
            day: 1
            month: 1
            year: 1970
            sec: 0
            yday: 1
            isdst: false
            --]]

            print("%A, %B: " .. os.date("%A, %B", tval))
            print("%x: " .. os.date("%x", tval))
            print("%m/%d/%y: " .. os.date("%m/%d/%y", tval))
        end
    }
)

oslibTest:registerCase(
    {
        key = "clock",
        f = function() 
            local c1 = os.clock()
            print("calulating sin(1) to sin(2^23)...")
            for index=1, 2^23 do
                local x = math.sin(index)
            end
            print(string.format("time consumed: %.2f", os.clock() - c1))
        end
    }
)

oslibTest:registerCase(
    {
        key = "getenv",
        f = function()
            print("el## os.getenv(PATH): " .. os.getenv("PATH"))
        end
    }
)

oslibTest:registerCase(
    {
        key = "execute",
        f = function()
            os.execute("ls -l")
        end
    }
)

oslibTest.test = function(self)
    for k,case in pairs(self.cases) do
        if not case.skip then
            print(string.format("===================== case: %s =====================", case.key))
            if type(case.f) ~= "function"  then
                print(string.format("-- skip case: %s, not a function", case.key))
            else
                case.f()
            end
            print(string.format("===================== end of case: %s =====================\n", case.key))
        end
    end
end

oslibTest.cases["time"].skip    = false
oslibTest.cases["date"].skip    = false
oslibTest.cases["clock"].skip   = false
oslibTest.cases["getenv"].skip  = false
oslibTest.cases["execute"].skip = false

oslibTest:test()

