# Ocular Scores Project
## Morphograph external

- Ocular Scores, featuring Morphograph
- Summary:  Analyze an audio buffer and export graphic score elements

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Installation

To get started with Morphograph, you need to download a release from the [Releases Section](https://github.com/CNMAT/morphograph/releases)
(These instructions assume you have Max 8+ installed)

- quit Max
- place the unzipped folder into a directory that is included in Max's search path
- launch Max
- follow instructions in help file

## Usage

The Morphograph external is configured by authoring a dictionary with specific keys and sending it to the inlet of the object.

**Dictionary format:** Current keys include 'filename', 'shape', 'style' (drawing style), and a nested dictionary named `descmap` (descriptor mapping).  This is where the user's choices for mapping from the spectral analysis outputs to shape parameters in the graph will occur.  Currently we are limited to one mapping per feature, based on a limitation that dictionaries have.  In the future, we'll include the ability to map a single feature to many shape parameters.  There is also a nested dictionary named `transform`, but it should be know that this can be omitted in favor of editing the attributes of the object itself and is mostly useful for dynamically altering the bounding rect of the graph before rendering.

Here is an example dictionary: 

```
{
	"filename" : "thetest.svg",
	"shape" : "ellipses",
	"style" : "fill",
	"descmap" : 	{
		"energy" : "rotation",
		"speccentr" : "ylocation",
		"hfc" : "size",
		"speckurt" : "xscale"
	},
	"transform" : 	{
		"width" : 700,
		"height" : 350,
		"zoom" : 1
	}
}
```

**Rendering:** Rendering is accomplished by sending a path to a folder via the `set_path` message, and issuing the `process` message to the object.  Note that if you've changed buffers you'll need to issue this message again to see an updated result.

**Introspection:** A `bang` to the inlet will post relevant information about `morphograph`'s state.  You can send the message `view` to see the buffer that is currently associated with the object.  The set of attributes can be viewed in the object's inspector.

**Writing:**  The filename of the output SVG is given based on the key "filename", and needs to be if you don't want to overwrite the previous file.  You can click the `write` message to bypass the standard writing mechanism and save a file to a location of your choice with a cusotm name.

*Please see the help file from a specific release for more information.*

## Features

- `morphograph` will analyze a max buffer and selectively (user-defined) map spectral features to shape parameters in an output graph (SVG file).
- the object accepts a max [dictionary] for graph configuration
- the `process` message will analyze and render a file to disk
- coarseness can be defined for resolution of output graph
- configure analysis & svg parameters with attributes
- normalization and standardization options for mapping to render coordinates (i.e., "rendermode")
- verbose mode for printing detail

## Contributing

*Please contact if you'd like to contribute to the project.*

## License

Copyright © 2023, 2024.  The Regents of the University of California (Regents). All Rights Reserved. Permission to use, copy, modify, and distribute this software and its documentation for educational, research, and not-for-profit purposes, without fee and without a signed licensing agreement, is hereby granted, provided that the above copyright notice, this paragraph and the following two paragraphs appear in all copies, modifications, and distributions. Contact The Office of Technology Licensing, UC Berkeley, 2150 Shattuck Avenue, Suite 510, Berkeley, CA 94720-1620, (510) 643-7201, for commercial licensing opportunities.

IN NO EVENT SHALL REGENTS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF REGENTS HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS PROVIDED "AS IS." REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

## Acknowledgments

**Credits:**
Commissioned by, and developed for [Linda Bouchard](https://lindabouchard.com/)

**Authors, R&D:**
Jeffrey Lubow and Carmine Cella, inspired by work by Joseph Browne

**Current maintainers:**
[Jeffrey Lubow](https://github.com/equilet), [Carmine Cella](https://github.com/CarmineCella)

If you have any questions or suggestions, feel free to open an [issue](https://github.com/CNMAT/morphograph/issues) or contact the maintainers. We hope you enjoy using Morphograph!
