
/**
 * @file
 * Override some Tabledrag functionality.
 */

/**
 * If the dragged row has a class of 'tabledrag-parent-locked', check the rows with which it might get swapped.
 * If the row it gets swapped with has a different  parent, block the swap by returning false.
 * This will prevent the locked child from being dragged to another parent.
 *
 * @override Drupal.tableDrag.row.isValidSwap
 */
// Keep the original implementation - we still need it.
Drupal.tableDrag.prototype.row.prototype._isValidSwap = Drupal.tableDrag.prototype.row.prototype.isValidSwap;
Drupal.tableDrag.prototype.row.prototype.isValidSwap = function(row) {
  if ($(this.element).hasClass('tabledrag-parent-locked')) {
    var nextRow;
    if (this.direction == 'down') {
      nextRow = $(row).next('tr').get(0);
    }
    else {
      nextRow = row;
    }

    if (nextRow && $('.taxonomy_term_hierarchy-parent', this.element).val() !== $('.taxonomy_term_hierarchy-parent', nextRow).val()) {
      return false;
    }
    else if (!nextRow && this.direction == 'down') {
      // If there's no next row and we're going down, we might jump out of the group. Prevent this by
      // blocking anyway. It's not completely ideal, but necessary.
      return false;
    }
  }

  // Return the original result.
  return this._isValidSwap(row);
}

/**
 * If the dragged row has a class of 'tabledrag-parent-locked', disable the indentation for the duration of
 * the drag. Store the old indentation setting in _indentEnabled.
 *
 * @override Drupal.tableDrag.dragRow
 */
// Keep the original implementation - we still need it.
Drupal.tableDrag.prototype._dragRow = Drupal.tableDrag.prototype.dragRow;
Drupal.tableDrag.prototype.dragRow = function(event, self) {
  if (self.rowObject && $(self.rowObject.element).hasClass('tabledrag-parent-locked')) {
    if (self.indentEnabled) {
      self._indentEnabled = true;
      self.indentEnabled = false;
    }
  }

  return self._dragRow(event, self);
}

/**
 * Restore the original indentation setting, if needed.
 *
 * @override Drupal.tableDrag.dragRow
 */
// Keep the original implementation - we still need it.
Drupal.tableDrag.prototype._dropRow = Drupal.tableDrag.prototype.dropRow;
Drupal.tableDrag.prototype.dropRow = function(event, self) {
  if (self._indentEnabled !== null) {
    self.indentEnabled = true;
    self._indentEnabled = null;
  }

  return self._dropRow(event, self);
}
