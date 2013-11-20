#!/usr/bin/ruby

Id        = ['id']
Coreattrs = Id + ['class', 'style', 'title']
I18n      = ['lang', 'xml:lang', 'dir']
Stdevents = ['onclick', 'ondblclick', 'onmousedown', 'onmouseup', 'onmouseover', 'onmousemove', 'onmouseout', 'onkeypress', 'onkeydown', 'onkeyup']
Focus     = ['accesskey', 'tabindex', 'onfocus', 'onblur']
Cellalign = ['align', 'char', 'charoff', 'valign']
Attrs     = Coreattrs + I18n


### define lists ###
id        = [] # Id
coreattrs = [] # Coreattrs
i18n      = [] # I18n
stdevents = [] # Stdevents
focus     = [] # Focus
cellalign = [] # Cellalign
attrs     = [] # Attrs
######################

# Penser aux attributs #FIXED comme xmlns pour <html>
@@tags = {
### Base classes ###
#     'QwuiDomInternationalizedElement'               => {:parent => 'QwuiDomElement',                   :required => [], :events => [], :optional => I18n},
#     'QwuiDomStandardAttributesElement' => {:parent => 'QwuiDomInternationalizedElement',               :required => [], :events => [], :optional => Coreattrs},
#     'QwuiDomFocusAttributesElement'    => {:parent => 'QwuiDomStandardAttributesElement', :required => [], :events => [], :optional => Focus},
#     'QwuiDomCellAttributesElement'     => {:parent => 'QwuiDomStandardAttributesElement', :required => [], :events => [], :optional => Cellalign},
####################

    'base'       => {:parent => 'QwuiDomElement',                   :required => ['href'],         :events => [],                                 :optional => id},
    'script'     => {:parent => 'QwuiDomElement',                   :required => ['type'],         :events => [],                                 :optional => id + ['charset', 'src', 'defer']},
    'param'      => {:parent => 'QwuiDomElement',                   :required => [],               :events => [],                                 :optional => id + ['name', 'value', 'valuetype', 'type']},

    'html'       => {:parent => 'QwuiDomInternationalizedElement',               :required => [],               :events => [],                                 :optional => id + i18n},
    'title'      => {:parent => 'QwuiDomInternationalizedElement',               :required => [],               :events => [],                                 :optional => id + i18n},
    'head'       => {:parent => 'QwuiDomInternationalizedElement',               :required => [],               :events => [],                                 :optional => id + i18n + ['profile']},
    'meta'       => {:parent => 'QwuiDomInternationalizedElement',               :required => ['content'],      :events => [],                                 :optional => id + i18n + ['http-equiv', 'name', 'scheme']},
    'style'      => {:parent => 'QwuiDomInternationalizedElement',               :required => ['type'],         :events => [],                                 :optional => id + i18n + ['media', 'title']},

    'br'         => {:parent => 'QwuiDomElement',                   :required => [],               :events => [],                                 :optional => Coreattrs}, # Should Inherit QwuiCoreAttributesElement

    'noscript'   => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'div'        => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'p'          => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'h1'         => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'h2'         => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'h3'         => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'h4'         => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'h5'         => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'h6'         => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'ul'         => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'ol'         => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'li'         => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'dl'         => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'dt'         => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'dd'         => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'address'    => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'hr'         => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'pre'        => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'span'       => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'em'         => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'strong'     => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'dfn'        => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'code'       => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'samp'       => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'kbd'        => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'var'        => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'cite'       => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'abbr'       => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'acronym'    => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'sub'        => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'sup'        => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'tt'         => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'i'          => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'b'          => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'big'        => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'small'      => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'caption'    => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'fieldset'   => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs},
    'body'       => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents + ['onload', 'onunload'], :optional => attrs},
    'bdo'        => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs}, # dir is required.
    'map'        => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs + ['name']}, # id is required
    'blockquote' => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs + ['cite']},
    'ins'        => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs + ['cite' + 'datetime']},
    'del'        => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs + ['cite' + 'datetime']},
    'q'          => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs + ['cite']},
    'link'       => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs + ['charset', 'href', 'hreflang', 'type', 'rel', 'rev', 'media']},
    'legend'     => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs + ['accesskey']},
    'object'     => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs + ['declare',  'classid', 'codebase', 'data', 'type', 'codetype', 'archive', 'standby', 'height', 'width', 'usemap', 'name', 'tabindex']},
    'label'      => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs + ['for', 'accesskey', 'onfocus', 'onblur']},
    'select'     => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs + ['name', 'size', 'multiple', 'disabled', 'tabindex', 'onfocus', 'onblur', 'onchange']},
    'option'     => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs + ['selected', 'disabled', 'label', 'value']},
    'table'      => {:parent => 'QwuiDomStandardAttributesElement', :required => [],               :events => stdevents,                          :optional => attrs + ['summary', 'width', 'border', 'frame', 'rules', 'cellspacing', 'cellpadding']},
    'img'        => {:parent => 'QwuiDomStandardAttributesElement', :required => ['src', 'alt'],   :events => stdevents,                          :optional => attrs + ['longdesc', 'height', 'width', 'usemap', 'ismap']},
    'form'       => {:parent => 'QwuiDomStandardAttributesElement', :required => ['action'],       :events => stdevents,                          :optional => attrs + ['method', 'enctype', 'onsubmit', 'onreset', 'accept', 'accept-charset']},
    'optgroup'   => {:parent => 'QwuiDomStandardAttributesElement', :required => ['label'],        :events => stdevents,                          :optional => attrs + ['disabled']},

    'a'          => {:parent => 'QwuiDomFocusAttributesElement',    :required => [],               :events => stdevents,                          :optional => attrs + focus + ['charset', 'type', 'name', 'href', 'hreflang', 'rel', 'rev', 'shape', 'coords']},
    'button'     => {:parent => 'QwuiDomFocusAttributesElement',    :required => [],               :events => stdevents,                          :optional => attrs + focus + ['name', 'value', 'type', 'disabled']},
    'input'      => {:parent => 'QwuiDomFocusAttributesElement',    :required => [],               :events => stdevents,                          :optional => attrs + focus + ['type', 'name', 'value', 'checked', 'disabled', 'readonly', 'size', 'maxlength', 'src', 'alt', 'usemap', 'onselect', 'onchange', 'accept']},
    'area'       => {:parent => 'QwuiDomFocusAttributesElement',    :required => ['alt'],          :events => stdevents,                          :optional => attrs + focus + ['coords', 'href', 'nohref']},
    'textarea'   => {:parent => 'QwuiDomFocusAttributesElement',    :required => ['rows', 'cols'], :events => stdevents,                          :optional => attrs + focus + ['name', 'disabled', 'readonly', 'onselect', 'onchange']},

    'thead'      => {:parent => 'QwuiDomCellAttributesElement',     :required => [],               :events => stdevents,                          :optional => attrs + cellalign},
    'tfoot'      => {:parent => 'QwuiDomCellAttributesElement',     :required => [],               :events => stdevents,                          :optional => attrs + cellalign},
    'tbody'      => {:parent => 'QwuiDomCellAttributesElement',     :required => [],               :events => stdevents,                          :optional => attrs + cellalign},
    'tr'         => {:parent => 'QwuiDomCellAttributesElement',     :required => [],               :events => stdevents,                          :optional => attrs + cellalign},
    'colgroup'   => {:parent => 'QwuiDomCellAttributesElement',     :required => [],               :events => stdevents,                          :optional => attrs + cellalign + ['span' + 'width']},
    'col'        => {:parent => 'QwuiDomCellAttributesElement',     :required => [],               :events => stdevents,                          :optional => attrs + cellalign + ['span' + 'width']},
    'th'         => {:parent => 'QwuiDomCellAttributesElement',     :required => [],               :events => stdevents,                          :optional => attrs + cellalign + ['abbr', 'axis', 'headers', 'scope', 'rowspan', 'colspan']},
    'td'         => {:parent => 'QwuiDomCellAttributesElement',     :required => [],               :events => stdevents,                          :optional => attrs + cellalign + ['abbr', 'axis', 'headers', 'scope', 'rowspan', 'colspan']},
}

def print_attributes_counts()
    attributes_counts = {}
    @@tags.each_pair { |tag, categories|
        categories.each_value { |l|
            l.each { |a|
                if attributes_counts.has_key?(a)
                    attributes_counts[a] = attributes_counts[a] + 1
                else
                    attributes_counts[a] = 1
                end
            }
        }
    }
    attributes_counts.each_pair { |key, value|
        puts "#{key}"#,#{value}"
    }
end

def cpp_case(tag)
    modified = {
        'noscript'          => 'noScript',
        'fieldset'          => 'fieldSet',
        'optgroup'          => 'optGroup',
        'textarea'          => 'textArea',
        'colgroup'          => 'colGroup',
        'longdesc'          => 'longDesc',
        'usemap'            => 'useMap',
        'cellpadding'       => 'cellPadding',
        'onreset'           => 'onReset',
        'cellspacing'       => 'cellSpacing',
        'accesskey'         => 'accessKey',
        'citedatetime'      => 'citeDateTime',
        'rowspan'           => 'rowSpan',
        'accept-charset'    => 'acceptCharset',
        'spanwidth'         => 'spanWidth',
        'onmousemove'       => 'onMouseMove',
        'onload'            => 'onLoad',
        'onselect'          => 'onSelect',
        'hreflang'          => 'hrefLang',
        'tabindex'          => 'tabIndex',
        'onunload'          => 'onUnload',
        'onmouseup'         => 'onMouseUp',
        'onsubmit'          => 'onSubmit',
        'onkeydown'         => 'onKeyDown',
        'nohref'            => 'noHref',
        'charoff'           => 'charOff',
        'codetype'          => 'codeType',
        'maxlength'         => 'maxLength',
        'onmousedown'       => 'onMouseDown',
        'onmouseover'       => 'onMouseOver',
        'ismap'             => 'isMap',
        'onkeypress'        => 'onKeyPress',
        'enctype'           => 'encType',
        'valuetype'         => 'valueType',
        'readonly'          => 'readOnly',
        'onblur'            => 'onBlur',
        'onkeyup'           => 'onKeyUp',
        'colspan'           => 'colSpan',
        'classid'           => 'classId',
        'xml:lang'          => 'xmlLang',
        'onchange'          => 'onChange',
        'onmouseout'        => 'onMouseOut',
        'onfocus'           => 'onFocus',
        'standby'           => 'standBy',
        'http-equiv'        => 'httpEquiv',
        'onclick'           => 'onClick',
        'ondblclick'        => 'onDblClick',
    }
    if (modified.has_key?(tag))
        return modified[tag]
    end
    return tag
end

def generate_classes()
    @@tags.each_pair { |tag, categories|
        parent = categories[:parent]
        required = categories[:required]
        optional = categories[:optional] + categories[:events]
        generate_header(tag, parent, required, optional)
        generate_implementation(tag, parent, required, optional)
    }
end

def upcase_first_char(str)
    return str[0].chr.upcase + str[1..-1]
end

def classname(tag)
    return "QwuiDomTag#{upcase_first_char(tag)}"
end

def generate_header(tag, parent, required_atts, optional_atts)
    header = File.new(classname(tag) + '.h', 'w')
    h_guard = "QT_WUI_DOM_TAG_#{tag.upcase}_H"
    c = classname(tag)
    header.write(
"#ifndef #{h_guard}
#define #{h_guard}

#include <QtWui/#{parent}>

class #{c} : public #{parent}
{
public:
    /**
     * @param parent the parent element.
     */
    #{c}(#{parent}* parent = NULL);
    virtual ~#{c}();
    virtual QString tagName() const;

")
    (required_atts + optional_atts).each { |attr|
        cpp_attr = cpp_case(attr)
        up_cpp_attr = upcase_first_char(cpp_attr)
        header.write(
"    QString #{cpp_attr}() const;
    void set#{up_cpp_attr}(const QString& v);
    void unset#{up_cpp_attr}();

")
    }
    header.write(
"};

#endif // #{h_guard}
")
    header.close
end

def generate_implementation(tag, parent, required_atts, optional_atts)
    impl = File.new(classname(tag) + '.cpp', 'w')
    c = classname(tag)
    impl.write(
"#include <QtWui/#{c}>

#{c}::#{c}(#{parent}* parent) :
    #{parent}(parent)
{
}

#{c}::~#{c}()
{
}

QString #{c}::tagName() const
{
    return \"#{tag}\";
}

")
    required_atts.each { |attr|
        cpp_attr = cpp_case(attr)
        up_cpp_attr = upcase_first_char(cpp_attr)
        impl.write(
"QString #{c}::#{cpp_attr}() const
{
    return requiredProperty(\"#{attr}\");
}

void #{c}::set#{up_cpp_attr}(const QString& v)
{
    setRequiredProperty(\"#{attr}\", v);
}

void #{c}::unset#{up_cpp_attr}()
{
    unsetRequiredProperty(\"#{attr}\");
}

")
    }

    optional_atts.each { |attr|
        cpp_attr = cpp_case(attr)
        up_cpp_attr = upcase_first_char(cpp_attr)
        impl.write(
"QString #{c}::#{cpp_attr}() const
{
    return optionalProperty(\"#{attr}\");
}

void #{c}::set#{up_cpp_attr}(const QString& v)
{
    setOptionalProperty(\"#{attr}\", v);
}

void #{c}::unset#{up_cpp_attr}()
{
    unsetOptionalProperty(\"#{attr}\");
}

")
    }
    impl.close
end

generate_classes()
