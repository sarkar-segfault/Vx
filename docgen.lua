#!/usr/bin/env lua

local function emit(file)
  local hndl = io.open("Headers/Vx/" .. file .. ".h", "r")
  assert(hndl, "failed to read file")

  local text = hndl:read("*a")
  hndl:close()

  local out = io.open("docs/" .. file .. ".md", "w")
  assert(out, "failed to open out file")

  out:write("---\nlayout: page\n---\n")

  for comment in string.gmatch(text, "/%*%*(.-)%*%*/") do
    out:write(comment)
  end

  out:close()
end

os.execute("mkdir docs")
emit("Vx")
emit("Event")
emit("Window")
emit("Context")
