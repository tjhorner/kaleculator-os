#include "initialisation_parameter_controller.h"
#include <assert.h>
#include <math.h>

namespace Graph {

InitialisationParameterController::InitialisationParameterController(Responder * parentResponder, GraphWindow * graphWindow) :
  ViewController(parentResponder),
  m_selectableTableView(SelectableTableView(this, this, Metric::TopMargin, Metric::RightMargin,
    Metric::BottomMargin, Metric::LeftMargin)),
  m_graphWindow(graphWindow)
{
  m_cells[0].setText("Trigonometrique");
  m_cells[1].setText("Abscisses entieres");
  m_cells[2].setText("Orthonorme");
  m_cells[3].setText("Reglage de base");

}

const char * InitialisationParameterController::title() const {
  return "Zoom predefini";
}

View * InitialisationParameterController::view() {
  return &m_selectableTableView;
}

void InitialisationParameterController::didBecomeFirstResponder() {
  m_selectableTableView.selectCellAtLocation(0, 0);
  app()->setFirstResponder(&m_selectableTableView);
}

bool InitialisationParameterController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::OK) {
    switch (m_selectableTableView.selectedRow()) {
      case 0:
      // TODO: if mode == degree, xmin = -600, xmax = 600
        m_graphWindow->setTrigonometric();
        break;
      case 1:
      {
        m_graphWindow->roundAbscissa();
        break;
      }
      case 2:
      {
        m_graphWindow->normalize();
        break;
      }
      case 3:
        m_graphWindow->setDefault();
        break;
      default:
        return false;
    }
    m_graphWindow->initCursorPosition();
    StackViewController * stack = (StackViewController *)parentResponder();
    stack->pop();
    return true;
  }
  return false;
}

int InitialisationParameterController::numberOfRows() {
  return k_totalNumberOfCells;
};


TableViewCell * InitialisationParameterController::reusableCell(int index) {
  assert(index >= 0);
  assert(index < k_totalNumberOfCells);
  return &m_cells[index];
}

int InitialisationParameterController::reusableCellCount() {
  return k_totalNumberOfCells;
}

KDCoordinate InitialisationParameterController::cellHeight() {
  return 35;
}

}
