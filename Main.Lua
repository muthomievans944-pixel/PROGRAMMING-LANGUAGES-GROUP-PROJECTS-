-- Question 2: M-Pesa Transaction Verification and Recovery (20 Marks)

-- a. Represent each transaction as an independent coroutine (4 marks)
function transaction(id, balance, amount)
    local status = "received"
    coroutine.yield(status)   -- b. Yield after every stage (4 marks)

    -- c. Reject transactions with insufficient funds (4 marks)
    if balance < amount then
        return "failed: insufficient funds"
    end

    status = "customer details checked"
    coroutine.yield(status)

    status = "balance verified"
    coroutine.yield(status)

    status = "transaction authorized"
    coroutine.yield(status)

    status = "receipt generated"
    return status
end

-- d. Scheduler design (5 marks)
function scheduler(transactions)
    for i, co in ipairs(transactions) do
        while coroutine.status(co) ~= "dead" do
            local ok, result = coroutine.resume(co)
            if not ok then
                print("Transaction " .. i .. " error: " .. result)
                break
            elseif result then
                print("Transaction " .. i .. " status: " .. result)
                if string.find(result, "failed") then
                    -- stop failed transaction, do not resume dead coroutines
                    break
                end
            end
        end
    end
end

-- Example usage
local t1 = coroutine.create(function() return transaction(1, 500, 200) end)
local t2 = coroutine.create(function() return transaction(2, 100, 300) end) -- insufficient funds
local t3 = coroutine.create(function() return transaction(3, 1000, 100) end)

scheduler({t1, t2, t3})

-- e. Why state is preserved after yield() (3 marks)
-- In Lua, when a coroutine yields, its local variables, stack, and program counter
-- are saved. On resume, execution continues exactly where it left off, with the
-- same preserved state. This allows transactions to pause and resume seamlessly.
