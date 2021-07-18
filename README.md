# Fantastic Perspective UE4.25 Movie Render Queue Compatibility Plugin

In `UE4.25` there was introduced `Movie Render Queue` plugin that is a successor to the Sequencer Render Movie feature. In `UE4.25` `Movie Render Queue` was not finally designed and has not got support for render view extensions. To work with it I have forked the `UE4.25` internal plugin and added support for using Fantastic Perspective. Here it is.

The addon is prebuilt for `Win64`, for `MacOS` and `Linux` you need to compile it yourself

## Installation
Additional plugin is available in releases: [ue4.25-render-passes-v1](https://github.com/AzazKamaz/UE-FantasticPerspective/releases/tag/ue4.25-render-passes-v1/)

Create dir "Plugins" in the project directory and unzip the archive there. The project directory must be like this:
```bash
├── Plugins
│   ├── FantasticPerspectiveRenderPasses
│   │   ├── FantasticPerspectiveRenderPasses.uplugin
│   ├── * (any other project-local plugins)
├── MyCoolProject.uproject
├── * (any other project files)
```

## Usage
To enable `Fantastic Perspective` in `Movie Render Queue`:
1. Open render settings in the `Movie Render Queue` tab
2. Add `Fantastic Perspective Deferred Rendering` setting
3. Disable or delete default `Deferred Rendering`
Also, you can do the same in project settings to use it by default

## What about different UE versions?
- below `UE4.25` there was no `Movie Render Queue`
- above `UE4.25` `Movie Render Queue` supports view extensions so the plugin works with it on its own
