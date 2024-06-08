# VisioneREmotion

Visioner implementation based on reading images from `input` folder and reading scene from a webcam. Expects images of following types:

- `input/object_good_*` - image of an object for positive response
- `input/object_bad_*` - image of an object for negative response

In theory, reads all major image formats, but tested only with `jpg` and `png`.
