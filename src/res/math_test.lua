local fname = {
    "rad", -- return rad from degree 
    "deg", -- return degree from rad 
}

local sin = math.sin
local cos = math.cos

local mathtest = {}

function mathtest.angle()
    local d = 30
    local sind = sin(math.rad(d))
    print("el## " .. string.format("sin(%.2f)=%.2f", d, sind))
    print("el## " .. string.format("sin(%.2f(rad)) = %.2f", math.rad(d), sind))
    local radd = math.rad(60) -- about 1.0 rad. 
    print("el## " .. string.format("cos(%.2f)=%.2f", radd, cos(radd)))
end

function mathtest.test()
    mathtest.angle()
end

mathtest.test()

