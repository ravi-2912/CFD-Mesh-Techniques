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
USer32.lib
```

### Installing

Install Visual Studio 2013 or higher, build the project from within the Visual Studio and it should start running.
In case, there are build errors for "Entry Point" implement the following steps

```
Project Properties > Linker > Advanced > Entry Point  = Main
Project Properties > Linker > System > SubSystem = Windows(/SUBSYSTEM:WINDOWS)
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone who's code was used
* Inspiration
* etc
