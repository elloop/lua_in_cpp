-- require 'math'
-- local x = math.random()
-- width  = math.max(x*10, 8)

-- if getenv("display") == "yes" then
if false then
    width = 100
    height = 200
else
    width = 1
    height = 2
end

background = {
    r = 120,
    g = 200,
    b = 255
}

function add(x, y)
    return x + y
end

function concat(str, n)
    -- print(str .. tostring(n))
end

function fufudezheng(x, y)
    -- print(type(x))
    -- print(type(y))
    if not x and not y then
        return true
    elseif x and y then
        return true
    else
        return false
    end
end

