#include "buildxml.h"

XMLBuilder::XMLBuilder(const QString& docName, bool instr) : m_doc(docName)
{
    QDomProcessingInstruction instructions = m_doc.createProcessingInstruction("xml", XML_INSTRUCTION_CONTENT);
    if (instr)
        m_doc.appendChild(instructions);
}

XMLBuilder& XMLBuilder::begin(const QString& tagName) throw(XMLException)
{
    if (tagName.isEmpty())
        throw XMLException(EMPTY_TAG_NAME);

    m_currentElement = m_doc.createElement(tagName);
    appendElement( m_currentElement );

    m_elementsStack.push(m_currentElement);

    return *this;
}

XMLBuilder& XMLBuilder::end() throw(XMLException)
{
    if (m_elementsStack.isEmpty())
        throw XMLException(TAG_NOT_STARTED);

    m_currentElement = m_elementsStack.pop();

    return *this;
}

XMLBuilder& XMLBuilder::attr(const QString& attrName, const QString& content) throw(XMLException)
{
    if (attrName.isEmpty())
        throw XMLException(EMPTY_ATTR_NAME);

    if (m_currentElement.isNull())
        throw XMLException(COULD_NOT_ADD_ATTR);

    m_currentElement.setAttribute(attrName, content);

    return *this;
}

XMLBuilder& XMLBuilder::add(const QString& tagName, const QString& content) throw(XMLException) {
    if (tagName.isEmpty())
        throw XMLException(EMPTY_TAG_NAME);

    m_currentElement = m_doc.createElement( tagName );
    appendElement( m_currentElement );

    QDomText textNode = m_doc.createTextNode( content );
    m_currentElement.appendChild( textNode );

    return *this;
}

QString XMLBuilder::getXML() const {
    return m_doc.toString();
}

void XMLBuilder::appendElement(const QDomElement& element)
{
    if (m_elementsStack.isEmpty())
        m_doc.appendChild(element);
    else
    {
        QDomElement currentRoot = m_elementsStack.top();
        currentRoot.appendChild(element);
    }
}
