# ASEngine Command Line Interface (CLI)

## Overview

This Command Line Interface (CLI) provides a set of commands to manage and build projects using a specified configuration file. The following commands are available:

- `help`: Show documentation.
- `status`: Get the status of the project.
- `run`: Build the project using default settings.
- `build`: Build the project for a specific platform.
- `generate-project`: Generate a new project.
- `generate-component`: Generate a new component.
- `generate-system`: Generate a new system.
- `generate-module`: Generate a new module.
- `generate-resource`: Generate a new resource.

## Usage

### `help`

Displays the documentation for the available commands.

```bash
$ asengine help
```

### `status`

Gets the status of the project.

```bash
$ asengine status
```

### `run`

Builds the project using default settings.

```bash
$ asengine run
```

### `build`

Builds the project for a specific platform.

```bash
$ asengine build <platform>
```

- `<platform>`: The target platform for the build (e.g., "linux").

### `generate-project`

Generates a new project.

```bash
$ asengine generate-project <project-name>
```

- `<project-name>`: The name of the new project.

### `generate-component`

Generates a new component.

```bash
$ asengine generate-component <component-name>
```

- `<component-name>`: The name of the new component.

### `generate-system`

Generates a new system.

```bash
$ asengine generate-system <system-name>
```

- `<system-name>`: The name of the new system.

### `generate-module`

Generates a new module.

```bash
$ asengine generate-module <module-name>
```

- `<module-name>`: The name of the new module.

### `generate-resource`

Generates a new resource.

```bash
$ asengine generate-resource <resource-name>
```

- `<resource-name>`: The name of the new resource.

## Notes

- For commands that require additional arguments, make sure to provide the required input as described in the documentation.
