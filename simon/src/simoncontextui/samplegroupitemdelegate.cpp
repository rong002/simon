#include "samplegroupitemdelegate.h"
#include "simoncontextdetection/contextmanager.h"
#include "simonscenarios/trainingmanager.h"
#include "simonsound/soundserver.h"
#include <QComboBox>
#include <KDebug>

SampleGroupItemDelegate::SampleGroupItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget* SampleGroupItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    QComboBox *sampleGroupBox = new QComboBox(parent);

    sampleGroupBox->setEditable(true);

    QStringList availableSampleGroups;

    availableSampleGroups << SoundServer::defaultSampleGroup();
    availableSampleGroups << SoundServer::getInputDeviceDefaultSampleGroups();
    availableSampleGroups << TrainingManager::getInstance()->getPrompts()->sampleGroups();
    availableSampleGroups << ContextManager::instance()->getSampleGroups();
    //TODO: make sample groups without enough training data shaded gray and italicized

    availableSampleGroups.removeDuplicates();
    sampleGroupBox->addItems(availableSampleGroups);
    sampleGroupBox->setCurrentIndex(0);

    return sampleGroupBox;
}

void SampleGroupItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *sampleGroupBox = qobject_cast<QComboBox*>(editor);

    QString sampleGroup = index.data().toString();

    if (sampleGroupBox->findText(sampleGroup) >= 0)
    {
        sampleGroupBox->setCurrentIndex(sampleGroupBox->findText(sampleGroup));
    }
    else
    {
        sampleGroupBox->addItem(sampleGroup);
        sampleGroupBox->setCurrentIndex(sampleGroupBox->findText(sampleGroup));
    }
}

void SampleGroupItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *sampleGroupBox = qobject_cast<QComboBox*>(editor);
    QString sampleGroup = sampleGroupBox->currentText();

    kDebug() << "setting current model data" << sampleGroup;

    model->setData(index, QVariant(sampleGroup));

    if (sampleGroupBox->findText(sampleGroup) < 0)
    {
        sampleGroupBox->addItem(sampleGroup);
        sampleGroupBox->setCurrentIndex(sampleGroupBox->findText(sampleGroup));
    }
}