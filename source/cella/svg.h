// svg_utils.h

#ifndef SVG_UTILS_H
#define SVG_UTILS_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include <iostream>

    // Utility XML/String Functions.
    template <typename T>
    std::string attribute(std::string const & attribute_name,
        T const & value, std::string const & unit = "")
    {
        std::stringstream ss;
        ss << attribute_name << "=\"" << value << unit << "\" ";
        return ss.str();
    }
    std::string elemStart(std::string const & element_name)
    {
        return "\t<" + element_name + " ";
    }
    std::string elemEnd(std::string const & element_name)
    {
        return "</" + element_name + ">\n";
    }
    std::string emptyElemEnd()
    {
        return "/>\n";
    }

    // Quick optional return type.  This allows functions to return an invalid
    //  value if no good return is possible.  The user checks for validity
    //  before using the returned value.
    template <typename T>
    class optional
    {
    public:
        optional<T>(T const & type)
            : valid(true), type(type) { }
        optional<T>() : valid(false), type(T()) { }
        T * operator->()
        {
            // If we try to access an invalid value, an exception is thrown.
            if (!valid)
                throw std::exception();

            return &type;
        }
        // Test for validity.
        bool operator!() const { return !valid; }
    private:
        bool valid;
        T type;
    };

    struct Dimensions
    {
        Dimensions(double width, double height) : width(width), height(height) { }
        Dimensions(double combined = 0) : width(combined), height(combined) { }
        double width;
        double height;
    };

    struct pPoint
    {
        pPoint(double x = 0, double y = 0) : x(x), y(y) { }
        double x;
        double y;
    };
    optional<pPoint> getMinPoint(std::vector<pPoint> const & pPoints)
    {
        if (pPoints.empty())
            return optional<pPoint>();

        pPoint min = pPoints[0];
        for (unsigned i = 0; i < pPoints.size(); ++i) {
            if (pPoints[i].x < min.x)
                min.x = pPoints[i].x;
            if (pPoints[i].y < min.y)
                min.y = pPoints[i].y;
        }
        return optional<pPoint>(min);
    }
    optional<pPoint> getMaxPoint(std::vector<pPoint> const & pPoints)
    {
        if (pPoints.empty())
            return optional<pPoint>();

        pPoint max = pPoints[0];
        for (unsigned i = 0; i < pPoints.size(); ++i) {
            if (pPoints[i].x > max.x)
                max.x = pPoints[i].x;
            if (pPoints[i].y > max.y)
                max.y = pPoints[i].y;
        }
        return optional<pPoint>(max);
    }

    // Defines the dimensions, scale, origin, and origin offset of the document.
    struct Layout
    {
        enum Origin { TopLeft, BottomLeft, TopRight, BottomRight };

        Layout(Dimensions const & dimensions = Dimensions(400, 300), Origin origin = BottomLeft,
            double scale = 1, pPoint const & origin_offset = pPoint(0, 0))
            : dimensions(dimensions), scale(scale), origin(origin), origin_offset(origin_offset) { }
        Dimensions dimensions;
        double scale;
        Origin origin;
        pPoint origin_offset;
    };

    // Convert coordinates in user space to SVG native space.
    double translateX(double x, Layout const & layout)
    {
        if (layout.origin == Layout::BottomRight || layout.origin == Layout::TopRight)
            return layout.dimensions.width - ((x + layout.origin_offset.x) * layout.scale);
        else
            return (layout.origin_offset.x + x) * layout.scale;
    }

    double translateY(double y, Layout const & layout)
    {
        if (layout.origin == Layout::BottomLeft || layout.origin == Layout::BottomRight)
            return layout.dimensions.height - ((y + layout.origin_offset.y) * layout.scale);
        else
            return (layout.origin_offset.y + y) * layout.scale;
    }
    double translateScale(double dimension, Layout const & layout)
    {
        return dimension * layout.scale;
    }

    class Serializeable
    {
    public:
        Serializeable() { }
        virtual ~Serializeable() { };
        virtual std::string toString(Layout const & layout) const = 0;
    };

    class Color : public Serializeable
    {
    public:
        enum Defaults { Transparent = -1, Aqua, Black, Blue, Brown, Cyan, Fuchsia,
            Green, Lime, Magenta, Orange, Purple, Red, Silver, White, Yellow };

        Color(int r, int g, int b) : transparent(false), red(r), green(g), blue(b) { }
        Color(Defaults color)
            : transparent(false), red(0), green(0), blue(0)
        {
            switch (color)
            {
                case Aqua: assign(0, 255, 255); break;
                case Black: assign(0, 0, 0); break;
                case Blue: assign(0, 0, 255); break;
                case Brown: assign(165, 42, 42); break;
                case Cyan: assign(0, 255, 255); break;
                case Fuchsia: assign(255, 0, 255); break;
                case Green: assign(0, 128, 0); break;
                case Lime: assign(0, 255, 0); break;
                case Magenta: assign(255, 0, 255); break;
                case Orange: assign(255, 165, 0); break;
                case Purple: assign(128, 0, 128); break;
                case Red: assign(255, 0, 0); break;
                case Silver: assign(192, 192, 192); break;
                case White: assign(255, 255, 255); break;
                case Yellow: assign(255, 255, 0); break;
                default: transparent = true; break;
            }
        }
        virtual ~Color() { }
        std::string toString(Layout const &) const
        {
            std::stringstream ss;
            if (transparent)
                ss << "transparent";
            else
                ss << "rgb(" << red << "," << green << "," << blue << ")";
            return ss.str();
        }
    private:
            bool transparent;
            int red;
            int green;
            int blue;

            void assign(int r, int g, int b)
            {
                red = r;
                green = g;
                blue = b;
            }
    };

    class Fill : public Serializeable
    {
    public:
        Fill(Color::Defaults color) : color(color) { }
        Fill(Color color = Color::Transparent)
            : color(color) { }
        std::string toString(Layout const & layout) const
        {
            std::stringstream ss;
            ss << attribute("fill", color.toString(layout));
            return ss.str();
        }
    private:
        Color color;
    };

    class Stroke : public Serializeable
    {
    public:
        Stroke(double width = -1, Color color = Color::Transparent)
            : width(width), color(color) { }
        std::string toString(Layout const & layout) const
        {
            // If stroke width is invalid.
            if (width < 0)
                return std::string();

            std::stringstream ss;
            ss << attribute("stroke-width", translateScale(width, layout)) << attribute("stroke", color.toString(layout));
            return ss.str();
        }
    private:
        double width;
        Color color;
    };

    class Font : public Serializeable
    {
    public:
        Font(double size = 12, std::string const & family = "Verdana") : size(size), family(family) { }
        std::string toString(Layout const & layout) const
        {
            std::stringstream ss;
            ss << attribute("font-size", translateScale(size, layout)) << attribute("font-family", family);
            return ss.str();
        }
    private:
        double size;
        std::string family;
    };

    class Shape : public Serializeable
    {
    public:
        Shape(Fill const & fill = Fill(), Stroke const & stroke = Stroke())
            : fill(fill), stroke(stroke) { }
        virtual ~Shape() { }
        virtual std::string toString(Layout const & layout) const = 0;
        virtual void offset(pPoint const & offset) = 0;
    protected:
        Fill fill;
        Stroke stroke;
    };
    template <typename T>
    std::string vectorToString(std::vector<T> collection, Layout const & layout)
    {
        std::string combination_str;
        for (unsigned i = 0; i < collection.size(); ++i)
            combination_str += collection[i].toString(layout);

        return combination_str;
    }

    class Circle : public Shape
    {
    public:
        Circle(pPoint const & center, double diameter, Fill const & fill,
            Stroke const & stroke = Stroke())
            : Shape(fill, stroke), center(center), radius(diameter / 2) { }
        std::string toString(Layout const & layout) const
        {
            std::stringstream ss;
            ss << elemStart("circle") << attribute("cx", translateX(center.x, layout))
                << attribute("cy", translateY(center.y, layout))
                << attribute("r", translateScale(radius, layout)) << fill.toString(layout)
                << stroke.toString(layout) << emptyElemEnd();
            return ss.str();
        }
        void offset(pPoint const & offset)
        {
            center.x += offset.x;
            center.y += offset.y;
        }
    private:
        pPoint center;
        double radius;
    };

    class Elipse : public Shape
    {
    public:
        Elipse(pPoint const & center, double width, double height,
            Fill const & fill = Fill(), Stroke const & stroke = Stroke())
            : Shape(fill, stroke), center(center), radius_width(width / 2),
            radius_height(height / 2) { }
        std::string toString(Layout const & layout) const
        {
            std::stringstream ss;
            ss << elemStart("ellipse") << attribute("cx", translateX(center.x, layout))
                << attribute("cy", translateY(center.y, layout))
                << attribute("rx", translateScale(radius_width, layout))
                << attribute("ry", translateScale(radius_height, layout))
                << fill.toString(layout) << stroke.toString(layout) << emptyElemEnd();
            return ss.str();
        }
        void offset(pPoint const & offset)
        {
            center.x += offset.x;
            center.y += offset.y;
        }
    private:
        pPoint center;
        double radius_width;
        double radius_height;
    };

    class Rectangle : public Shape
    {
    public:
        Rectangle(pPoint const & edge, double width, double height,
            Fill const & fill = Fill(), Stroke const & stroke = Stroke())
            : Shape(fill, stroke), edge(edge), width(width),
            height(height) { }
        std::string toString(Layout const & layout) const
        {
            std::stringstream ss;
            ss << elemStart("rect") << attribute("x", translateX(edge.x, layout))
                << attribute("y", translateY(edge.y, layout))
                << attribute("width", translateScale(width, layout))
                << attribute("height", translateScale(height, layout))
                << fill.toString(layout) << stroke.toString(layout) << emptyElemEnd();
            return ss.str();
        }
        void offset(pPoint const & offset)
        {
            edge.x += offset.x;
            edge.y += offset.y;
        }
    private:
        pPoint edge;
        double width;
        double height;
    };

    class Line : public Shape
    {
    public:
        Line(pPoint const & start_pPoint, pPoint const & end_pPoint,
            Stroke const & stroke = Stroke())
            : Shape(Fill(), stroke), start_pPoint(start_pPoint),
            end_pPoint(end_pPoint) { }
        std::string toString(Layout const & layout) const
        {
            std::stringstream ss;
            ss << elemStart("line") << attribute("x1", translateX(start_pPoint.x, layout))
                << attribute("y1", translateY(start_pPoint.y, layout))
                << attribute("x2", translateX(end_pPoint.x, layout))
                << attribute("y2", translateY(end_pPoint.y, layout))
                << stroke.toString(layout) << emptyElemEnd();
            return ss.str();
        }
        void offset(pPoint const & offset)
        {
            start_pPoint.x += offset.x;
            start_pPoint.y += offset.y;

            end_pPoint.x += offset.x;
            end_pPoint.y += offset.y;
        }
    private:
        pPoint start_pPoint;
        pPoint end_pPoint;
    };

    class Polygon : public Shape
    {
    public:
        Polygon(Fill const & fill = Fill(), Stroke const & stroke = Stroke())
            : Shape(fill, stroke) { }
        Polygon(Stroke const & stroke = Stroke()) : Shape(Color::Transparent, stroke) { }
        Polygon & operator<<(pPoint const & pPoint)
        {
            pPoints.push_back(pPoint);
            return *this;
        }
        std::string toString(Layout const & layout) const
        {
            std::stringstream ss;
            ss << elemStart("polygon");

            ss << "points=\"";
            for (unsigned i = 0; i < pPoints.size(); ++i)
                ss << translateX(pPoints[i].x, layout) << "," << translateY(pPoints[i].y, layout) << " ";
            ss << "\" ";

            ss << fill.toString(layout) << stroke.toString(layout) << emptyElemEnd();
            return ss.str();
        }
        void offset(pPoint const & offset)
        {
            for (unsigned i = 0; i < pPoints.size(); ++i) {
                pPoints[i].x += offset.x;
                pPoints[i].y += offset.y;
            }
        }
    private:
        std::vector<pPoint> pPoints;
    };

    class Polyline : public Shape
    {
    public:
        Polyline(Fill const & fill = Fill(), Stroke const & stroke = Stroke())
            : Shape(fill, stroke) { }
        Polyline(Stroke const & stroke = Stroke()) : Shape(Color::Transparent, stroke) { }
        Polyline(std::vector<pPoint> const & pPoints,
            Fill const & fill = Fill(), Stroke const & stroke = Stroke())
            : Shape(fill, stroke), pPoints(pPoints) { }
        Polyline & operator<<(pPoint const & pPoint)
        {
            pPoints.push_back(pPoint);
            return *this;
        }
        std::string toString(Layout const & layout) const
        {
            std::stringstream ss;
            ss << elemStart("polyline");

            ss << "Points=\"";
            for (unsigned i = 0; i < pPoints.size(); ++i)
                ss << translateX(pPoints[i].x, layout) << "," << translateY(pPoints[i].y, layout) << " ";
            ss << "\" ";

            ss << fill.toString(layout) << stroke.toString(layout) << emptyElemEnd();
            return ss.str();
        }
        void offset(pPoint const & offset)
        {
            for (unsigned i = 0; i < pPoints.size(); ++i) {
                pPoints[i].x += offset.x;
                pPoints[i].y += offset.y;
            }
        }
        std::vector<pPoint> pPoints;
    };

    class Text : public Shape
    {
    public:
        Text(pPoint const & origin, std::string const & content, Fill const & fill = Fill(),
             Font const & font = Font(), Stroke const & stroke = Stroke())
            : Shape(fill, stroke), origin(origin), content(content), font(font) { }
        std::string toString(Layout const & layout) const
        {
            std::stringstream ss;
            ss << elemStart("text") << attribute("x", translateX(origin.x, layout))
                << attribute("y", translateY(origin.y, layout))
                << fill.toString(layout) << stroke.toString(layout) << font.toString(layout)
                << ">" << content << elemEnd("text");
            return ss.str();
        }
        void offset(pPoint const & offset)
        {
            origin.x += offset.x;
            origin.y += offset.y;
        }
    private:
        pPoint origin;
        std::string content;
        Font font;
    };

    // Sample charting class.
    class LineChart : public Shape
    {
    public:
        LineChart(Dimensions margin = Dimensions(), double scale = 1,
                  Stroke const & axis_stroke = Stroke(.5, Color::Purple))
            : axis_stroke(axis_stroke), margin(margin), scale(scale) { }
        LineChart & operator<<(Polyline const & polyline)
        {
            if (polyline.pPoints.empty())
                return *this;

            polylines.push_back(polyline);
            return *this;
        }
        std::string toString(Layout const & layout) const
        {
            if (polylines.empty())
                return "";

            std::string ret;
            for (unsigned i = 0; i < polylines.size(); ++i)
                ret += polylineToString(polylines[i], layout);

            return ret + axisString(layout);
        }
        void offset(pPoint const & offset)
        {
            for (unsigned i = 0; i < polylines.size(); ++i)
                polylines[i].offset(offset);
        }
    private:
        Stroke axis_stroke;
        Dimensions margin;
        double scale;
        std::vector<Polyline> polylines;

        optional<Dimensions> getDimensions() const
        {
            if (polylines.empty())
                return optional<Dimensions>();

            optional<pPoint> min = getMinPoint(polylines[0].pPoints);
            optional<pPoint> max = getMaxPoint(polylines[0].pPoints);
            for (unsigned i = 0; i < polylines.size(); ++i) {
                if (getMinPoint(polylines[i].pPoints)->x < min->x)
                    min->x = getMinPoint(polylines[i].pPoints)->x;
                if (getMinPoint(polylines[i].pPoints)->y < min->y)
                    min->y = getMinPoint(polylines[i].pPoints)->y;
                if (getMaxPoint(polylines[i].pPoints)->x > max->x)
                    max->x = getMaxPoint(polylines[i].pPoints)->x;
                if (getMaxPoint(polylines[i].pPoints)->y > max->y)
                    max->y = getMaxPoint(polylines[i].pPoints)->y;
            }

            return optional<Dimensions>(Dimensions(max->x - min->x, max->y - min->y));
        }
        std::string axisString(Layout const & layout) const
        {
            optional<Dimensions> dimensions = getDimensions();
            if (!dimensions)
                return "";

            // Make the axis 10% wider and higher than the data Points.
            double width = dimensions->width * 1.1;
            double height = dimensions->height * 1.1;

            // Draw the axis.
            Polyline axis(Color::Transparent, axis_stroke);
            axis << pPoint(margin.width, margin.height + height) << pPoint(margin.width, margin.height)
                << pPoint(margin.width + width, margin.height);

            return axis.toString(layout);
        }
        std::string polylineToString(Polyline const & polyline, Layout const & layout) const
        {
            Polyline shifted_polyline = polyline;
            shifted_polyline.offset(pPoint(margin.width, margin.height));

            std::vector<Circle> vertices;
            for (unsigned i = 0; i < shifted_polyline.pPoints.size(); ++i)
                vertices.push_back(Circle(shifted_polyline.pPoints[i], getDimensions()->height / 30.0, Color::Black));

            return shifted_polyline.toString(layout) + vectorToString(vertices, layout);
        }
    };

    class Document
    {
    public:
        Document(std::string const & file_name, Layout layout = Layout())
            : file_name(file_name), layout(layout) { }

        Document & operator<<(Shape const & shape)
        {
            body_nodes_str += shape.toString(layout);
            return *this;
        }
        std::string toString() const
        {
            std::stringstream ss;
            ss << "<?xml " << attribute("version", "1.0") << attribute("standalone", "no")
                << "?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" "
                << "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n<svg "
                << attribute("width", layout.dimensions.width, "px")
                << attribute("height", layout.dimensions.height, "px")
                << attribute("xmlns", "http://www.w3.org/2000/svg")
                << attribute("version", "1.1") << ">\n" << body_nodes_str << elemEnd("svg");
            return ss.str();
        }
        bool save() const
        {
            std::ofstream ofs(file_name.c_str());
            if (!ofs.good())
                return false;

            ofs << toString();
            ofs.close();
            return true;
        }
    private:
        std::string file_name;
        Layout layout;

        std::string body_nodes_str;
    };

#endif // SVG_UTILS_H

// EOF

