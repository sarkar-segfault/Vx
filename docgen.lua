#!/usr/bin/env lua
--[[
  Documentation generator for this project.
  This file uses project internals and documentation
  schemes to extract doc comments and sometimes definitions.
  Do not modify this unless you know what you're dealing with.
]]--

local files = io.open("docs/files.md", "w")
assert(files, "failed to open files")

files:write("---\nlayout: page\ntitle: Files\n---\n")
files:write("Vx has a relatively short number of header files. The documentation for public ones is listed below:\n")

local i = 0

local function emit(file)
  local hndl = io.open("Headers/Vx/" .. file .. ".h", "r")
  assert(hndl, "failed to read file")

  local text = hndl:read("*a")
  hndl:close()

  local out = io.open("docs/" .. file .. ".md", "w")
  assert(out, "failed to open out file")

  i = i + 1
  files:write(tostring(i) .. ". [" .. file .. ".h](/" .. file .. ".md)\n")

  out:write("---\nlayout: page\ntitle: " .. file .. ".h\n---\n")

  for comment, code in string.gmatch(text, "/%*%*(.-)%*%*/\n([^\n]*)") do
    local result1, _ = comment:gsub("  ", "")
    out:write(result1)

    if comment:find("## Method") or comment:find("## Function") or comment:find("## Functional macro") then
      local result2, _ = code:gsub("Vx__Expose ", "")
      out:write("\n```c\n" .. result2 .. "\n```\n")
    end
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
emit("Flag")
emit("Event")
emit("Status")
emit("Window")
emit("Context")
