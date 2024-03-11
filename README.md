# Seabiscuit: TiDE Driver Display

Built with Qt/QML. UI built in Qt Design Studio. Backend built in Qt Creator.

* [Software Setup Guide](#software-setup-guide)
* [Project Overview](#project-overview)
* [About Qt](#about-qt)
  * [Qt CAN Bus Plugin](#qt-can-bus-plugin)
  * [Licensing](#licensing)
* [Warning System](#warning-system)

## Software Setup Guide

Download both Qt Creator and Qt Design Studio from the [Qt main website](https://www.qt.io/) (**Products** > **Qt Development Tools** > **Download Qt and Products** > **Qt Design Studio** > Get **Qt Design Studio**).

Qt can be configured with Git by following the steps in [this guide](https://doc.qt.io/qtcreator/creator-vcs-git.html).

## Project Overview

The driver display is a Windows application built with Qt (pronounced “cute”). It serves as the main dashboard inside the boat, displaying essential information for the driver to check with a glance. We use the following hardware components:

* Tablet: [Dell Latitude 12 Rugged Tablet](https://www.dell.com/support/manuals/en-us/latitude-7202-tablet/lat12rugged7202_ug/specifications?guid=guid-dc9c68cb-09a4-4844-b470-4bb1e155c8b1&lang=en-us)
* CAN adapter: [Vector VN1610](https://www.vector.com/us/en/products/products-a-z/hardware/network-interfaces/vn16xx/#c66319) (connects to tablet via USB)

We designed this display based on those of similar speedboats, simplifying our last shore dashboard (Snowfinkle).

| Snowfinkle Shore Dashboard  | TiDE Main Display |
| :----: | :----: |
| <img width="451" alt="Screenshot 2024-01-25 at 5 06 59 PM" src="https://github.com/uofmelectricboat/.github/assets/101139170/56c28f31-ae76-4181-b6f9-cfb3ef4fe4a0"> |  <img width="451" alt="Screenshot 2024-01-25 at 5 06 59 PM" src="https://github.com/uofmelectricboat/.github/assets/101139170/70f9f015-ac96-4432-ae9e-e0d2c5744185"> |

## About Qt

Qt is open-source cross-platform software for creating graphical user interfaces that run on major desktop platforms and mobile or embedded platforms. It is not a coding language–it is a framework written in C++. See more on the [Qt wiki](https://wiki.qt.io/About_Qt).

Qt provides different IDEs for different use cases:

* **Qt Creator** is more programmer-focused, providing tools for coding, debugging, and profiling. It allows users to open/edit an .ui or .qml file and create Qt/C++ applications.
* **Qt Design Studio** is a UI design tool that focuses on creating user interfaces.

They should be used together to develop a Qt Quick application with a visual UI designer.

### Qt CAN Bus Plugin

Qt’s Serial Bus module allows us to access the CAN bus via the VectorCAN plugin, which works with our CAN adapter. See the official documentation here:

* [QtSerialBus](https://doc.qt.io/qt-6/qtserialbus-index.html)
* [QtCANBus](https://doc.qt.io/qt-6/qtcanbus-backends.html)
* [VectorCAN plugin](https://doc.qt.io/qt-6/qtserialbus-vectorcan-overview.html)

### Licensing
Qt is a free tool under GPLv3 and LGPLv3. Software created with Qt can be released under any approved open source license.

## Warning System
In the event of any issues, the main display must promptly alert the driver. We use a color-coded system to indicate operational health: yellow denotes warning levels, while red signifies a dangerous state. However, it is not always safe to assume that the driver is continuously monitoring the display. A stretch goal for this project is to incorporate an audible alarm system, which would alert the driver when they need to check the display for potential issues.
