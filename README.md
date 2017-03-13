# Meshing Techniques for CFD

Microsoft Visual Studio C++ .NET (2013) and Legacy OpenGL project to demonstrate three diferent meshing techniques for Computation Fluid Dynamics (CFD). The following three meshing algorithms are used in this project:

1. Multi Surface Methods (MSM)
2. Transfinite Interpolation (TFI)
3. Elliptic Partial Differential Equations (PDE)

## Getting Started

Just download and open the Visual Studio Solution file with extension "sln" from within the Visual Studio.

### Prerequisites

The project depends on the following system libraries.

```
OpenGL32.lib
Glu32.lib
Gdi32.lib
User32.lib
And applicable dotNet Framework
```

### Installing

Install Visual Studio 2013 or higher, build the project from within the Visual Studio and it should start running.
In case, there are build errors for "Entry Point" implement the following steps

```
Project Properties > Linker > Advanced > Entry Point    = Main
Project Properties > Linker > System > SubSystem        = Windows(/SUBSYSTEM:WINDOWS)
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Microsoft Visual Studio](https://www.visualstudio.com/) 
* [Windows SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk)

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

GitHub default.

## Author

* Ravinder Singh

## License

This project is licensed under the Apache License v2.0 - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* [Chistian B. Allen](http://www.bris.ac.uk/engineering/people/christian-b-allen/index.html)
* [Purple Booth](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)
