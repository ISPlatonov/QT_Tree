#ifndef BUILDXML_H
#define BUILDXML_H

#include <QDomDocument>
#include <QDomElement>
#include <QStack>

#define XML_INSTRUCTION_CONTENT "version=\"1.0\" encoding=\"UTF-8\""

class XMLBuilder {
public:
    enum ErrorCode {
        EMPTY_TAG_NAME,
        EMPTY_ATTR_NAME,
        COULD_NOT_ADD_ATTR,
        TAG_NOT_STARTED
    };

    class XMLException : public std::exception
    {
    public:
        explicit XMLException(ErrorCode code) : m_code(code) {}
        ~XMLException() throw() {}

        const char* what() const throw() {
            switch( m_code ) {
            case EMPTY_TAG_NAME: return "Empty tag name!";
            case EMPTY_ATTR_NAME: return "Empty attribute name!";
            case COULD_NOT_ADD_ATTR: return "Could not add attribute!";
            case TAG_NOT_STARTED: return "There are no started tags!";
            default: return "Unknown error!";
            }
        }

    private:
        ErrorCode m_code;
    };

public:
    explicit XMLBuilder(const QString& docName = "", bool instr = true);

    XMLBuilder& begin(const QString& tagName) throw( XMLException);
    XMLBuilder& add(const QString& tagName, const QString& content) throw(XMLException);
    XMLBuilder& attr(const QString& attrName, const QString& content) throw(XMLException);
    XMLBuilder& end() throw( XMLException );

    QString getXML() const;

private:
    void appendElement(const QDomElement& element);

private:
    QDomDocument m_doc;
    QStack< QDomElement > m_elementsStack;
    QDomElement m_currentElement;
};

#endif // BUILDXML_H
