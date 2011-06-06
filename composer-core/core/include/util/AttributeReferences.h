#ifndef ATTRIBUTEREFERENCES_H
#define ATTRIBUTEREFERENCES_H

#include <QString>

namespace composer {
        namespace util {

/*!
 \brief Keep information about which pair (element, attribute) can
            refer a value of another pair (element, attribute).

 This class is mainly used to described the language profile.
*/
class AttributeReferences {
private:
    QString element, attr, /*!< TODO */
    ref_element, ref_attr; /*!< TODO */

public:
    /*!
     \brief Constructor.

     \param element The source Element.
     \param attr The source Attribute (should be an element's attribute).
     \param ref_element The target element.
     \param ref_attr The target attribute (should be an ref_element's
                        attribute).
    */
    AttributeReferences ( QString element,
                          QString attr,
                          QString ref_element,
                          QString ref_attr);

    /*!
     \brief Get the source element.

     \return QString the name of the source element.
    */
    QString getElement();
    /*!
     \brief Get the source attribute.

     \return QString the name of the source attribute.
    */
    QString getAttribute();
    /*!
     \brief Get the name of referred element.

     \return QString The name of the referred element.
    */
    QString getRefElement();
    /*!
     \brief Get the name of the referred attribute (an ref_element's attribute).

     \return QString The name of the referred attribute.
    */
    QString getRefAttribute();
};

}} //end namespace
#endif
