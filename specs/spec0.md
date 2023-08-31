# Spec 0
> NOTE: Spec 0 isn't really a spec just a way to make sure magik is self hostable and nothing else before 1.0.0 (Spec 1) and isn't meant to be used by anything

## Description
Spec 0 is the spec that magik 0.X.Y will use, it's designed to be the minimum to self host magik and nothing more.

## Example file:
```toml
spec = 0

[project]
name = "project_name"
version = "0.1.0"

src = "src"
obj = "obj"
bin = "bin"
lib = "lib"

deps = ["lib1", "lib2"]

[lib1]
src = "foo" # Relative to library dir

[lib2]
src = "bar" # Relative to library dir
```

## Keys
- **spec**: specification version
- **[project]**
  - **name**: Name of the project
  - **version**: Version string of the project follwing "X.Y.Z" (magor.minor.patch)
  - **src**: Source directory
  - **obj**: Object directory
  - **bin**: Binary directory
  - <a name="project_lib">**lib**: Library directory</a>
  - **deps**: Array of all librarys needed
- [\<libname>]
  - **src**: Source directory relative to [**[project].lib**](#project_lib)

## Notes:
- Support for only 1 project