#!/usr/bin/env lua

local function emit(file)
  local hndl = io.open("Headers/Vx/" .. file .. ".h", "r")
  assert(hndl, "failed to read file")

  local text = hndl:read("*a")
  hndl:close()

  local out = io.open("docs/" .. file .. ".md", "w")
  assert(out, "failed to open out file")

  out:write("---\nlayout: page\ntitle: " .. file .. ".h\n---\n")

  for comment, code in string.gmatch(text, "/%*%*(.-)%*%*/\n([^\n]*)") do
    local result1, _ = comment:gsub("  ", "")
    out:write(result1)

    if comment:find("## Method") or comment:find("## Function") or comment:find("## Functional macro") then
      local result2, _ = code:gsub("Vx__Expose ", "")
      out:write("\n```" .. result2 .. "```\n")
    end
  end

  out:close()
end

local index = io.open("docs/index.md", "w")
local readme = io.open("README.md", "r")
assert(index and readme, "failed to open files")

index:write("---\nlayout: page\ntitle: Vx\n---\n")
local result, _ = readme:read("*a"):gsub("^[^\n]*\n", "")
index:write(result)

emit("Vx")
emit("Event")
emit("Window")
emit("Context")
