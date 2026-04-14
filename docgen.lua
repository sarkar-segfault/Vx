#!/usr/bin/env lua

local function emit(file)
  local hndl = io.open("Headers/Vx/" .. file .. ".h", "r")
  assert(hndl, "failed to read file")

  local text = hndl:read("*a")
  hndl:close()

  local out = io.open("docs/" .. file .. ".md", "w")
  assert(out, "failed to open out file")

  out:write("---\nlayout: page\ntitle: ")

  local first = true
  for comment in string.gmatch(text, "/%*%*(.-)%*%*/") do
    if first then
      first = false
      local result, _ = text:match("([^\n]*)")
      out:write(result .. "\n---")
    end

    local result, _ = comment:gsub("  ", "")
    out:write(result)
  end

  out:close()
end

local index = io.open("docs/index.md", "w")
local readme = io.open("README.md", "r")
assert(index and readme, "failed to open files")

index:write("---\nlayout: home\ntitle: Vx\n---\n")
local result, _ = readme:read("*a"):gsub("^[^\n]*\n", "")
index:write(result)

emit("Vx")
emit("Event")
emit("Window")
emit("Context")
